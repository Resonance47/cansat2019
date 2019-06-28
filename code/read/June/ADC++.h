void servoinit ()
{
	DDRB |= 1<<4;
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01) | (1<<CS02);
}
void servorotate(unsigned char ugol)
{
	OCR0 = ugol;
}

void init_adc()// настройка аналого-цифрового преобразователя
{
	ADMUX|=0b01000000;
	_delay_ms(1000);
	ADCSRA |=(1<<ADEN);
	ADCSRA |=(1<<ADPS2|1<<ADPS1|1<<ADPS0);
}

unsigned int read_adc(unsigned char adc_input)// считывание с аналогового датчика
{
	ADMUX |= 0x07 & adc_input;
	ADCSRA |=(1<<ADSC);
	while((ADCSRA &(1<<ADIF))==0);
	return ADCW;
}


