#include <math.h>
#define pi 3.141592653589793238462643383279
class point
{
public:
	double oldlatitude;//������
	double oldlongitude;//�������
	double oldtime;
	double oldhigh;//���������� ����, ��� � ���� 47                                                                                                                                 (�����, ��� ������)
	double sigma;//��������������� �������, ��� ����, ����� ������ ��������� ������...
	double epsilon;//���������� �����, �������� �� ������ �� ���� ����� � ����, //!!!������ ��� ��� �� �������, � ������� ��������!!!//
	double geodez;//���� ���� ��� �������������� (�� ������ ����� ����� �����)
	double Rz;

	double latitude;//������
	double longitude;//�������
	double time;
	double timeTF;
	double high;//������ ����� ������

	double pointLa;//��������� ����� ����� ��, ���� ���� ��� ������� �����������
	double pointLo;//�������, ���� ������

	point(double la, double lo, double h, double t)
	/////////////////////���������� �����������, ��������� �������� � ������ ���///////////////////////////////////
	////���������� ����������� ������ 1 ���, ����� ��������� �������� ����� ����� 'UPDATE', ����� ��� ���������//// (�� ���, ����� ���-�� ������� 2 ������ ��������� xD)
	{
		latitude = la;
		longitude = lo;
		high = h;
		time = t;
		Rz = 6371000;

		oldlatitude = latitude;
		oldlongitude = longitude;
		oldtime = 0;
		oldhigh = 0;
	}
	void update(double la, double lo, double h, double t)
	//��������� �������� ������ ����� ���� �����//
	{
		oldlatitude = latitude;
		oldlongitude = longitude;
		oldhigh = high;
		oldtime = time;

		latitude = la;
		longitude = lo;
		high = h;
		time = t;
	}
// 	void duga()//https://docviewer.yandex.ru/view/0/?page=2&*=2GqKR3qBI%2Fkbw9FhJX1KXP1QhHt7InVybCI6Imh0dHA6Ly93d3cuZ2VvZ3IubXN1LnJ1L2NhZmVkcmEva2FydGEvZG9jcy9HT0svZ29rX2xlY3R1cmVfNC5wZGYiLCJ0aXRsZSI6Imdva19sZWN0dXJlXzQucGRmIiwibm9pZnJhbWUiOnRydWUsInVpZCI6IjAiLCJ0cyI6MTU2MDMzNDIwOTY0MiwieXUiOiI2OTUwNTY1NDcxNTYwMzMwOTc1Iiwic2VycFBhcmFtcyI6Imxhbmc9cnUmdG09MTU2MDMzNDE2OCZ0bGQ9cnUmbmFtZT1nb2tfbGVjdHVyZV80LnBkZiZ0ZXh0PSVEMCVCQSVEMCVCMCVEMCVCQSslRDElODMlRDAlQjclRDAlQkQlRDAlQjAlRDElODIlRDElOEMrJUQwJUI0JUQwJUJCJUQwJUI4JUQwJUJEJUQxJTgzKyVEMCVCNCVEMSU4MyVEMCVCMyVEMCVCOCslRDAlQkQlRDAlQjArJUQxJTg4JUQwJUIwJUQxJTgwJUQwJUI1KyVEMCVCRiVEMCVCRSslRDAlQkElRDAlQkUlRDAlQkUlRDElODAlRDAlQjQlRDAlQjglRDAlQkQlRDAlQjAlRDElODIlRDAlQjAlRDAlQkMrJUQxJTgyJUQwJUJFJUQxJTg3JUQwJUI1JUQwJUJBKyVEMCVCQSVEMCVCRSVEMCVCRCVEMSU4NiVEMCVCRSVEMCVCMiZ1cmw9aHR0cCUzQS8vd3d3Lmdlb2dyLm1zdS5ydS9jYWZlZHJhL2thcnRhL2RvY3MvR09LL2dva19sZWN0dXJlXzQucGRmJmxyPTImbWltZT1wZGYmbDEwbj1ydSZzaWduPWIxMmI3N2Q3OTVkYTg2YmUzM2EyMDczZmUwMTA1MzMwJmtleW5vPTAifQ%3D%3D&lang=ru
// 	//���� �������, �� ������ ������� ����� ����// ��� ����� ��������, ��������� � �������, ��������: +-3 �����
// 	{
// 		double signum = sin(latitude)*sin(oldlatitude) + cos(latitude)*cos(oldlatitude)*cos(longitude - oldlongitude);
// 		if (signum >= 0)
// 		{
// 			geodez = Rz*acos(signum);
// 		}
// 		else
// 		{
// 			geodez = Rz*(pi - abs(signum));
// 		}
// 	}
// 
// 	void sigmaTry()
// 	{
// 		sigma = atan((sin(latitude - oldlatitude)) / ((tan(longitude) / tan(oldlongitude)) - cos(latitude - oldlatitude)));//������ �� ��������� � ��
// 		epsilon = tan(oldlongitude) / sin(sigma);
// 		//����� ��-�� ������ �������� - ������� atan � �� �������� ��������� ��������, ���� ���, ����� ������ ��� ���������//
// 	}

	void TimeToFall()
	{
		if ((oldhigh - high) == 0 || (time - oldtime) == 0)
		{
			timeTF = 0;
		}
		else
		{
			//������� ����� �� ����������� ����� ������������� ������ �������� �����������//
			double deltaT = time - oldtime;
			double deltaH = oldhigh - high;
			double speed = deltaH / deltaT;
			if( (high/speed) >= 0 )
				timeTF = high / speed;
			else
				timeTF = - (high / speed);				
		}
	}

	// 	void poisk()
	// 	{
	// 		//��������� ����� �� ��������, ������ �� �������������, ������ 1.0//
	// 		//�� ��������, ��� ��� ���������� ������ ������, ����� ��� ����� ������� ������� update, �������������� �������������� �����//
	// 		duga();
	// 		sigmaTry();
	// 		TimeToFall();
	// 		double X;
	// 		int detect = 0;
	// 		double i = -2*pi; //���������� �����//
	// 		while(i<=2*pi)
	// 		{
	// 			X = acos((cos((geodez*timeTF)/(time-oldtime)) - sin(oldlongitude)*sin(i))/(cos(oldlongitude)*cos(i)));
	// 			if (abs(cos(sigma)*sin(X) + sin(sigma)*cos(X) - (tan(i) / (epsilon))) <= 0.001) //�������� ������� ����������� ������ ���� �� ������ ������ ����, ������� ����� 10^(-3), ����� ��� ��� 10^(-4)//
	// 			{
	// 				pointLo = i;
	// 				pointLa = asin(tan(pointLo) / epsilon) - sigma;
	// 				detect = 1;
	// 				break;
	// 			}
	// 			//cout << i;
	// 			i = i + 0.0001; //��� 0.0001//
	//
	// 		}
	// 	}
	void kostylchik()//��� ������ ���� ���** �� �������, ����� ����������� �����������, ��������� ��� �������
	{
		if ((time - oldtime) == 0)
		{
			pointLa = latitude;
			pointLo = longitude;
		}
		else
		{
			TimeToFall();
			pointLa = (((timeTF*(latitude - oldlatitude)) / (time - oldtime)) + latitude);
			pointLo = (((timeTF*(longitude - oldlongitude)) / (time - oldtime)) + longitude);
		}
	}
};
