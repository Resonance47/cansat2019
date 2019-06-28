#ifndef GPS_NEO6M_H_
#define GPS_NEO6M_H_

#include <string.h>

////////////////////////////////////////////////// Variables

double latitude = 0; // широта
bool hs_n_o; // север/юг ; N - true ; O - false
double longitude = 0; // долгота
bool hs_e_w; // запад/восток ; E - true ; W - false
double course_dir = 0; // направление курса в градусах
double speed_knots = 0; // скорость над поверхостью в узлах
double speed_kmh = 0; // скорость над поверхостью в км/ч
bool status = false; // статус ; A - данные верны ; V - данные не верны

char package[6];
unsigned int num_curr = 0;
unsigned int num_need = 0;

unsigned int mode = 5; // 0 - прием названия пакета ; 1 - приняли название пакета ; 2 - прием элемента ; 4 - ищем нужный элемент

buffer buf;

uint8_t data = 0;

////////////////////////////////////////////////// Functions

double array2double(char *arr)
{
	if (arr[0] == '\0') // если полученный массив пустой
		return 0.0;

	double data = 0.0;
	int i = 0;
	int j = -1;
	char symb;

	for (;;) // перенос части до запятой
	{
		symb = arr[i];
		if (symb == '.')
		break;
		data = (data * 10) + ((int)symb - '0');
		i++;
	}
	i++;
	for (;;) // перенос части после запятой
	{
		symb = arr[i];
		if (symb == '\0') // если массив закончился
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
	//////////////////// Прием данных, обновление переменных
	if (data == ',')
	{
		num_curr++;
		if (mode == 0) // если принимали название, то после приема ',' название заканчивается
		{
			mode = 1;
			strcpy(package, buf.read_all());
			buf.clear();
		}
		if (mode == 2) // если принимали элемент, то после приема ',' элемент заканчивается
		{
			mode = 4;

			////////// Заносим элемент в нужную переменную
			char *buf_data = buf.read_all();
			if(buf_data[0] == '\0')
			{
				goto save_elem; // чтобы данные после потери сигнала сохранились переходим по ссылке
			}
			
			if (!strcmp(package, "GPVTG"))
			{
				if (num_need == 1) // направление курса в градусах
					course_dir = array2double(buf_data);
				else if (num_need == 5) // скорость над поверхостью в км/ч
					speed_kmh = array2double(buf_data);
				else if (num_need == 7) // скорость над поверхостью в узлах
					speed_knots = array2double(buf_data);
			}
			else if (!strcmp(package, "GPGLL"))
			{
				if (num_need == 1) // широта
					latitude = array2double(buf_data);
				else if (num_need == 2) // север/юг
				{
					if (!strcmp("N", buf_data))
						hs_n_o = true;
					else
						hs_n_o = false;
				}
				else if (num_need == 3) // долгота
					longitude = array2double(buf_data);
				else if (num_need == 4) // запад/восток
				{
					if (!strcmp("E", buf_data))
						hs_e_w = true;
					else
						hs_e_w = false;
				}
				else if (num_need == 5) // время
					array2double(buf_data);
				else if (num_need == 6) // статус
				{
					if (!strcmp("A", buf_data))
						status = true;
					else
						status = false;
				}
			}
			save_elem:
			buf.clear();

			////////// Обновляем num_need
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
		if (mode == 0 || mode == 2) // если продолжаем принимать какие-то данные
			buf.add_one(data);
	}

	//////////////////// Выбор режимов для считывания данных
	if (data == '$')
	{
		mode = 0;
		num_curr = 0;
	}
	if (mode == 1) // если приняли название пакета, то обновляем num_need в зависимости от названия этого пакета
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
	if (mode == 4 && num_curr == num_need) // нашли нужный элемент
	{
		mode = 2;
	}
}



#endif /* GPS_NEO6M_H_ */