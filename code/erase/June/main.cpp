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


ISR(INT2_vect)
{
	//Uart_tr("ISR!");
	radio_writereg(STATUS,0b00101110);
	_delay_us(10);
}





int main(void)
{
	init_timer();

	//timer_datch_init();
	spi_init();
	i2c_init();
	i2c_init1();
	uart_init();
	_delay_ms(100);
	flash_init();
	Uart_tr("\nstart erase\n");
	flash_chip_erase();
	_delay_ms(15000);
	while(is_flash_busy());
	while(1)
	{
		Uart_tr("Ok\n");
		_delay_ms(100);
	}
}