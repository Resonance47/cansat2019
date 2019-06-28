#ifndef GPS_NEO6M_H_
#define GPS_NEO6M_H_

#include <string.h>

////////////////////////////////////////////////// Variables

double latitude = 0; // ������
bool hs_n_o; // �����/�� ; N - true ; O - false
double longitude = 0; // �������
bool hs_e_w; // �����/������ ; E - true ; W - false
double course_dir = 0; // ����������� ����� � ��������
double speed_knots = 0; // �������� ��� ����������� � �����
double speed_kmh = 0; // �������� ��� ����������� � ��/�
bool status = false; // ������ ; A - ������ ����� ; V - ������ �� �����

char package[6];
unsigned int num_curr = 0;
unsigned int num_need = 0;

unsigned int mode = 5; // 0 - ����� �������� ������ ; 1 - ������� �������� ������ ; 2 - ����� �������� ; 4 - ���� ������ �������

buffer buf;

uint8_t data = 0;

////////////////////////////////////////////////// Functions

double array2double(char *arr)
{
	if (arr[0] == '\0') // ���� ���������� ������ ������
		return 0.0;

	double data = 0.0;
	int i = 0;
	int j = -1;
	char symb;

	for (;;) // ������� ����� �� �������
	{
		symb = arr[i];
		if (symb == '.')
		break;
		data = (data * 10) + ((int)symb - '0');
		i++;
	}
	i++;
	for (;;) // ������� ����� ����� �������
	{
		symb = arr[i];
		if (symb == '\0') // ���� ������ ����������
		break;
		data = data + (((int)symb - 48) * pow(10, j));
		j--;
		i++;
	}
	return data;
}


////////////////////////////////////////////////// Interrupts

ISR(USART0_RX_vect)
{
	data = UDR0;
// 	char HA[2];
// 	HA[0] = data; HA[1]='\0';
// 	Uart_tr(HA);
	//////////////////// ����� ������, ���������� ����������
	if (data == ',')
	{
		num_curr++;
		if (mode == 0) // ���� ��������� ��������, �� ����� ������ ',' �������� �������������
		{
			mode = 1;
			strcpy(package, buf.read_all());
			buf.clear();
		}
		if (mode == 2) // ���� ��������� �������, �� ����� ������ ',' ������� �������������
		{
			mode = 4;

			////////// ������� ������� � ������ ����������
			char *buf_data = buf.read_all();
			if(buf_data[0] == '\0')
			{
				goto save_elem; // ����� ������ ����� ������ ������� ����������� ��������� �� ������
			}
			
			if (!strcmp(package, "GPVTG"))
			{
				if (num_need == 1) // ����������� ����� � ��������
					course_dir = array2double(buf_data);
				else if (num_need == 5) // �������� ��� ����������� � ��/�
					speed_kmh = array2double(buf_data);
				else if (num_need == 7) // �������� ��� ����������� � �����
					speed_knots = array2double(buf_data);
			}
			else if (!strcmp(package, "GPGLL"))
			{
				if (num_need == 1) // ������
					latitude = array2double(buf_data);
				else if (num_need == 2) // �����/��
				{
					if (!strcmp("N", buf_data))
						hs_n_o = true;
					else
						hs_n_o = false;
				}
				else if (num_need == 3) // �������
					longitude = array2double(buf_data);
				else if (num_need == 4) // �����/������
				{
					if (!strcmp("E", buf_data))
						hs_e_w = true;
					else
						hs_e_w = false;
				}
				else if (num_need == 5) // �����
					array2double(buf_data);
				else if (num_need == 6) // ������
				{
					if (!strcmp("A", buf_data))
						status = true;
					else
						status = false;
				}
			}
			save_elem:
			buf.clear();

			////////// ��������� num_need
			if (!strcmp(package, "GPVTG"))
			{
				if (num_need == 1)
					num_need = 5;
					else if (num_need == 5)
				num_need = 7;
			}
			else if (!strcmp(package, "GPGLL"))
			{
				if (num_need < 6)
					num_need++;
			}
		}
	}
	else
	{
		if (mode == 0 || mode == 2) // ���� ���������� ��������� �����-�� ������
			buf.add_one(data);
	}

	//////////////////// ����� ������� ��� ���������� ������
	if (data == '$')
	{
		mode = 0;
		num_curr = 0;
	}
	if (mode == 1) // ���� ������� �������� ������, �� ��������� num_need � ����������� �� �������� ����� ������
	{
		if (!strcmp(package, "GPVTG"))
		{
			num_need = 1;
			mode = 4;
		}
		else if (!strcmp(package, "GPGLL"))
		{
			num_need = 1;
			mode = 4;
		}
	}
	if (mode == 4 && num_curr == num_need) // ����� ������ �������
	{
		mode = 2;
	}
}



#endif /* GPS_NEO6M_H_ */