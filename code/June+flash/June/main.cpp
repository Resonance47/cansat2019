#include <avr/io.h>
#define F_CPU 8000000
#define BAUD 9600L
#define UBRRL_value (F_CPU/(BAUD*16)) - 1
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <math.h>


#define cosa 0.942
#define sina sqrt(1 - cosa*cosa)


void uart_init()
{
	UBRR0H =  (UBRRL_value)>>8;
	UBRR0L =  UBRRL_value;
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	UCSR0B = (1<<TXEN0) | (1<<RXEN0)| (1 << RXCIE0); //////////////разберись где нули//////////////
}

void   Uart_tr(char s[])
{
	unsigned char k;
	for (k=0; s[k]!=0; k++)
	{
		UDR0 = s[k];
		while (!(UCSR0A&(1<<UDRE0)));
	}
}
#define e  2.718281828459045235360287471352
#define ko 29.2177449

#include "i2c.h"
#include "i2c1.h"
#include "bmp.h"
#include "adxl.h"
#include "ds.h"
#include "E01-MC01SPC.h"
#include "si7021.h"
#include "mpu9250.h"
#include "ADC++.h"
#include "buffer.h"
#include "gps_neo6m.h"
#include "points.h"
#include "timer.h"
#include "spi.h"
#include "flash_w25q.h"
#include "eeprom.h"
#include "avalanche.h"



double h (double p, double p0, double T)
{
	double l = log(p/p0);
	double hr = - (l*T)*(ko);
	return hr;
}
double dm2dd2rad(double data_in)//перевод в радианы
{
	double data_out = 0;				//ddmm.mmm
	int d = (int)(data_in / 100);		//dd
	double m = (data_in - (d * 100));	//ddmm.mmm-dd00 -> mm.mmm
	data_out = d + m / 60;				//dd+mm.mm/100
	data_out = (data_out*180)/pi;
	return data_out;
}
double dm2dd(double data_in)
{	
	double data_out = 0;				//ddmm.mmm
	int d = (int)(data_in / 100);		//dd
	double m = (data_in - (d * 100));	//ddmm.mmm-dd00 -> mm.mmm
	data_out = d + m / 60;				//dd+mm.mm/100
	return data_out;
}
double radtograd(double data_in)//обратно 
{
	double data_out = (data_in*pi)/180;
	return data_out;
}


ISR(INT2_vect)
{
	//Uart_tr("ISR!");
	radio_writereg(STATUS,0b00101110);
	_delay_us(10);
}




int main(void)
{
	init_timer();
	_delay_ms(50);

	spi_init();
	_delay_ms(50);

	i2c_init();
	_delay_ms(50);
	
	i2c_init1();
	_delay_ms(50);
	
	uart_init();
	_delay_ms(50);
	
	mpu9250check();
	_delay_ms(100);
	
	Init_ADXL();
	_delay_ms(100);
	
	GET_ID();
	_delay_ms(500);
	
	BMP280_Begin();
	_delay_ms(100);
		
	DS18B20_init();
	_delay_ms(100);

	int32_t t;
	int32_t ti;

	uint32_t p;
	uint32_t alpha = 0; //угол под которым стоит спутник
	long int tds = 0;
	int hsi = 0;
	int tsi = 0;
	int micro = 0;
	int high = 0;
// 	uint64_t time1 = 0;}comment1
// 	uint64_t time2 = 0;}comment1
	
	
	t = read_T();
	_delay_ms(500);
	
	uint32_t p0 = read_P();
	uint32_t n=0;
	
	init_adc();
	_delay_ms(50);
	
	servoinit();
	_delay_ms(100);
	
	flash_init();
	_delay_ms(50);
	
	uart_init();
	_delay_ms(100);
	
	radio_init();
	_delay_ms(50);

	int ch_rad;
	char A[32] = {"HELLO_OK"};
	char DA[200];//дл€ юарта
	char RA[10];//дл€ радио
	ch_rad = radio_start();
	radio_assert_ce();
	DDRB |= (1<<6);
	EIMSK|=(1<<2);
	EICRA|=(1<<ISC21)|(0<<ISC20);
	sei();
// 	int x=0;
//  				while(1)
//  						{
// 					
//  							char DA[10];
//  							x=x+1;
//  							sprintf(A,"hello x=%d \n",x);
// 							uint8_t f;
//  							f=send_data((uint8_t*)A,32);
//  							sprintf(DA, "%d, %d\n", ch_rad, f);
//  							Uart_tr(DA);
//  							f=0;
//  							_delay_ms(1000);
// 					
//  					
//  					
//  						}////////end radio
	read Read;//mpu
	aval av(0, 0, 0, 0);//веро€тность
	point poi(latitude, longitude, 0, 0);//точка преземлени€// !высота в начале 0, как и врем€! //
	

	uint64_t adress = 0;
	bool protect = 0;
	bool eepromprotect = 0;

	_delay_ms(15000);//дл€ профилактики
//	time1 = getTime()*10000;//comment1

	while(1)
	{
		//
		sei();
		t = read_T();
		p = read_P();
		ti = t/100+273;
		tds = convert(temp());
		hsi = si_read_h();
		tsi = si_read_T();
		micro = read_adc(0);
		double highi = h (p, p0, ti);
		high = highi;
		
		GET_ACCEL();

		///////////////avalanche
		
		
		
		av.avalrefresh(alpha, micro, tsi, hsi);
		av.queen();
		av.queen2();
		av.queen3();
		
// 		sprintf(DA, "\nVeroyatnost iskluchitelnoy lavinnoy opasnosti = 0.%d \nVeroyatnost massovogo shoda lavin znachitelnogo ob'ema = 0.%d \nVeroyatnost togo, chto sneg v neustoychivom sostoyanii = 0.%d \nDlya tochnogo prognoza : 0.%d \n \n", (int)(av.vero*1000), (int)(av.vero2*1000), (int)(av.vero3*1000), (int)(av.paa*1000) );
// 		Uart_tr(DA);

		///////////////mpu
			
		
		int x = Read.mpu_read_Ax();
		int y = Read.mpu_read_Ay();
		int z = Read.mpu_read_Az();
		
// 		int gx = Read.mpu_read_hyroX();
// 		int gy = Read.mpu_read_hyroY();
// 		int gz = Read.mpu_read_hyroZ();
			
		int ax = int((x*cosa-z*sina));
		int ay = int((y));
		int az = int((z*cosa+x*sina));
				
// 			sprintf(DA, "la=%d, lo=%d, status=%d, x=%d, y=%d, z=%d, dx=%d, dy=%d, dz=%d\n", (int)(latitude*1000), (int)(longitude*1000), status, x, y, z, gx, gy, gz);
// 			Uart_tr(DA);
		
		/////////////////////////point

			
// 			time2 = getTime()*10000;//секуды* 10'000, нужно дл€ вывода в юарт./////}
// 			uint32_t timeC = (time2-time1);//врем€ на цикл в сек*10'000////////////}comment1
// 			time1 = time2;//"ќбнул€ем" врем€///////////////////////////////////////}
					
			poi.update(latitude, longitude, high, getTime());
			poi.kostylchik();

		///////////////////////radio
					
							//x=x+1;
							uint8_t f;
							sprintf(A,"%ldA %d %d %d\n", n, (uint16_t)ACCEL_X, (uint16_t)ACCEL_Y, (uint16_t)ACCEL_Z);//full
							f=send_data((uint8_t*)A,32);
							sprintf(RA, "%d, %d", ch_rad, f);
							//Uart_tr(RA);
							f=0;					
							_delay_ms(75);
					
					
					
							//x=x+1;
							sprintf(A,"%ldB %ld %ld %ld %d\n",n, p, t, tds, high);//full
							f=send_data((uint8_t*)A,32);
							sprintf(RA, "%d, %d", ch_rad, f);
							//Uart_tr(RA);
							f=0;
							_delay_ms(75);
			
					
							//x=x+1;
							sprintf(A,"%ldC %d %d\n",n,  tsi, hsi);//full
							f=send_data((uint8_t*)A,32);
							sprintf(RA, "%d, %d", ch_rad, f);
							//Uart_tr(RA);
							f=0;
							_delay_ms(75);
		
					
							//x=x+1;
							sprintf(A,"%ldD %d %d %d %d\n", n, (int)(av.vero*100), (int)(av.vero2*100), (int)(av.vero3*100), (int)(av.paa*100));//full
							f=send_data((uint8_t*)A,32);
							sprintf(RA, "%d, %d", ch_rad, f);
							//Uart_tr(RA);
							f=0;
							_delay_ms(75);
					
					
							//x=x+1;
							sprintf(A,"%ldE %ld %ld\n",n, (uint32_t)(poi.pointLa*10000), (uint32_t)(poi.pointLo*10000));//full
							f=send_data((uint8_t*)A,32);
							sprintf(RA, "%d, %d", ch_rad, f);
							//Uart_tr(RA);
							f=0;
							_delay_ms(75);
					
		
							//x=x+1
							sprintf(A,"%ldF %d %d %ld\n", n, (int)latitude, (int)longitude, alpha);//full
							f=send_data((uint8_t*)A,32);
							sprintf(RA, "%d, %d", ch_rad, f);
							//Uart_tr(RA);
							f=0;
										
					
		///////////////////open			
			if(high>30)
			{
				protect=1;
			}
			
			if(high<=20 && protect==1)
			{
				servorotate(50);
				protect=0;
				//PORTB |= (1<<6);////////////включи при пуске!
				_delay_ms(700);
				servorotate(0);
			}
				
				
				
			if(high>10 && eepromprotect == 0)
			{
				eepromprotect = 1;
				PORTB |= (1<<6);
				_delay_ms(100);
				PORTB &= ~(1 << 6);
			}
				
		poi.TimeToFall();	
						
		alpha = (uint32_t)(acos(ax/(9.8*100))*180/pi);
		
////////////////////eeprom///////
		if(eepromprotect == 1)
		{
			if(adress<4096)
			{
				EEPROM_write_2byte(adress, av.vero*100);
				adress+=2;
				EEPROM_write_2byte(adress, av.vero2*100);
				adress+=2;

				EEPROM_write_2byte(adress, av.vero3*100);
				adress+=2;
				
				EEPROM_write_2byte(adress, av.paa*100);
				adress+=2;

				EEPROM_write_4byte(adress, poi.pointLa*10000);
				adress+=4;

				EEPROM_write_4byte(adress, poi.pointLo*10000);
				adress+=4;

			}
		}
/////////////////////////
		
//////////Flash//////////

 		flashwrite(n, (int)ax, (int)ay, (int)az, (int)tsi, (int)hsi, (int)high, (int)0, (uint32_t)(poi.pointLa*100000), (uint32_t)(poi.pointLo*100000), (uint32_t)(latitude*100000), (uint32_t)(longitude*100000), (uint16_t)(av.vero*100), (uint16_t)(av.vero2*100), (uint16_t)(av.vero3*100), (uint16_t)(av.paa*100), (int)(alpha));
 		sprintf(DA, "%ld;%d;%d;%d;%d;%d;%d;%d;%ld;%ld;%ld;%ld;%d;%d;%d;%d;%d\n\n",n, (int)ax, (int)ay, (int)az, (int)tsi, (int)hsi, (int)high, (int)micro, (uint32_t)(poi.pointLa*100000), (uint32_t)(poi.pointLo*100000), (uint32_t)(latitude*100000), (uint32_t)(longitude*100000), (uint16_t)(av.vero*100), (uint16_t)(av.vero2*100), (uint16_t)(av.vero3*100), (uint16_t)(av.paa*100), (int)(alpha));
 		Uart_tr(DA);
		
		//sprintf(DA, "x = %ld; y = %ld; z = %ld; micro =%ld\n", (uint32_t)ACCEL_X, (uint32_t)(ACCEL_Y), (uint32_t)ACCEL_Z, (uint32_t)(micro));
		//Uart_tr(DA);
/////////////////////////
		n = n + 1;
	}

}