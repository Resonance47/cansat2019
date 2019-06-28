#include <math.h>
#define pi 3.141592653589793238462643383279
class point
{
public:
	double oldlatitude;//широта
	double oldlongitude;//долгота
	double oldtime;
	double oldhigh;//веротность того, что у меня 47                                                                                                                                 (шутка, это высота)
	double sigma;//вспомогательные цифирки, для того, чтобы узнать пожробнее перейд...
	double epsilon;//аналогично сигме, трогайте их только на свой страх и риск, //!!!УЧЕСТЬ ЧТО ЭТО НЕ ЭПИСЛОН, А ТАНГЕНС ЭПИСИЛОН!!!//
	double geodez;//дина дуги для интегрирования (ну просто очень умное слово)
	double Rz;

	double latitude;//широта
	double longitude;//долгота
	double time;
	double timeTF;
	double high;//скорее всего высота

	double pointLa;//собстенно здесь будет то, ради чего эта пирушка затеивалась
	double pointLo;//долгота, выше широта

	point(double la, double lo, double h, double t)
	/////////////////////простейший конструктор, заполняем значения в первый раз///////////////////////////////////
	////ИСПОЛЬЗУЕМ КОНСТРУКТОР ТОЛЬКО 1 РАЗ, ДАЛЕЕ ОБНОВЛЯЕМ ЗНАЧЕНИЯ ЧЕРЕЗ МЕТОД 'UPDATE', ИНАЧЕ ВСЕ НАКРОЕТСЯ//// (ну так, вдруг кто-то захочет 2 класса создавать xD)
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
	//обновляем значения именно через этот метод//
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
// 	//если коротко, то просто считаем длину дуги// Эта хрень работает, проверено и одобено, точность: +-3 метра
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
// 		sigma = atan((sin(latitude - oldlatitude)) / ((tan(longitude) / tan(oldlongitude)) - cos(latitude - oldlatitude)));//Смотри вк переписку с ИА
// 		epsilon = tan(oldlongitude) / sin(sigma);
// 		//плохо из-за потери точности - функция atan и ей подобные уменьшают точность, пока так, будем думать как исправить//
// 	}

	void TimeToFall()
	{
		if ((oldhigh - high) == 0 || (time - oldtime) == 0)
		{
			timeTF = 0;
		}
		else
		{
			//Считаем время до приземления через промежуточный расчет скорости приземления//
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
	// 		//Уравнение может не работать, ничего не гарантируется, версия 1.0//
	// 		//Не забываем, что для корректной работы метода, перед ним нужно вручную вызвать update, предварительно сконструировав класс//
	// 		duga();
	// 		sigmaTry();
	// 		TimeToFall();
	// 		double X;
	// 		int detect = 0;
	// 		double i = -2*pi; //переменная цикла//
	// 		while(i<=2*pi)
	// 		{
	// 			X = acos((cos((geodez*timeTF)/(time-oldtime)) - sin(oldlongitude)*sin(i))/(cos(oldlongitude)*cos(i)));
	// 			if (abs(cos(sigma)*sin(X) + sin(sigma)*cos(X) - (tan(i) / (epsilon))) <= 0.001) //Условная эпислон окрестность должна быть на прядок меньше шага, поэтому беоем 10^(-3), тогда как шаг 10^(-4)//
	// 			{
	// 				pointLo = i;
	// 				pointLa = asin(tan(pointLo) / epsilon) - sigma;
	// 				detect = 1;
	// 				break;
	// 			}
	// 			//cout << i;
	// 			i = i + 0.0001; //ШАГ 0.0001//
	//
	// 		}
	// 	}
	void kostylchik()//это просто если ниф** не работет, можно попробовать закостылить, используя эту функцию
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
