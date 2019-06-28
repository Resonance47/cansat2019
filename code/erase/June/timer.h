double second =0;
double msecond=0;


void init_timer()
{
	TCCR1B = (0<<CS12)|(1<<CS11)|(0<<CS10)|(0<<WGM12)|(0<<WGM13); // 8 +нормал
	TCCR1A  = (0<<WGM10)|(0<<WGM11);// режим normal
	TIMSK |= (1<<TOIE1); // разрешаем прерывание по переполнению таймера
}
void init_timer3()
{
	TCCR3B = (1<<CS32)|(0<<CS31)|(1<<CS30)|(0<<WGM32)|(0<<WGM33); //1024+нормал
	TCCR3A  = (0<<WGM30)|(0<<WGM31);// режим normal
	TIMSK |= (1<<TOIE3); // разрешаем прерывание по переполнению таймера
}
// ISR(TIMER3_OVF_vect)
// {
// 	TCNT3=0;
// }
ISR(TIMER1_OVF_vect)
{
	msecond=msecond + 65.536;
	
		if(msecond>=1000)
		{
		msecond = msecond-1000;
		second++;
		}
}

double getTime()
{
	double nowTime;
	nowTime = second + msecond/1000;
	return nowTime;
}