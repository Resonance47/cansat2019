/*#define SKIP_ROM         0xCC
#define CONVERT_T        0x44
#define READ_SCRATCHPAD  0xBE
#define Write_Scratchpad 0x4E
#define Copy_Scratchpad  0x48
#define USER_BYTE_1      0x7F
#define USER_BYTE_2      0xFF
#define DSCONFIG         0x3F

#define TS_DDR DDRA
#define TS_PORT PORTA
#define TS_PIN PINA
#define TS 2
#define TS_LOW TS_DDR |=1<<TS //0
#define TS_HIGH TS_DDR &=~(1<<TS)//1


char TS_find (void) // проверяем наличие датчика
{
	char SRO=SREG;
	cli();
	char device;
	TS_LOW;
	_delay_us(485);
	TS_HIGH;
	_delay_us(65);
	if((TS_PIN & (1<<TS))==0x00){
	device=1;

	}
	else
	{
		device=0;
		
	}
	SREG=SRO;
	_delay_us(420);
	return device;
}

void TS_write_bit(char bit) // отправляем 1 бит на датчик
{
	char SR1=SREG;
	cli();
	TS_LOW;
	_delay_us(2);
	if(bit) TS_HIGH;
	_delay_us(65);
	TS_HIGH;
	SREG=SR1;
}

void TS_write_byte(unsigned char c) // отправляем 1 байт на датчик
{
	char i;
	for(i=0;i<8;i++)
	{
		if((c&(1<<i))== 1<<i)
		TS_write_bit(1);
		else
		TS_write_bit(0);
	}
}

char TS_read_bit (void) // считываем 1 бит с датчика
{
	char SR2=SREG;
	cli();
	char TS_bitm;
	TS_LOW;
	_delay_us(2);
	TS_HIGH;
	_delay_us(13);
	TS_bitm=(TS_PIN & (1<<TS))>>TS;
	_delay_us(45);
	SREG=SR2;
	return TS_bitm;
}

unsigned char TS_read_byte() // считывем 1 байт с датчика
{
	char data=0,i;
	for(i=0;i<8;i++)
	data |=TS_read_bit()<<i;
	return data;
}

void DS18B20_init ()
{
	TS_write_byte(SKIP_ROM);
	TS_write_byte(Write_Scratchpad);
	TS_write_byte(USER_BYTE_1); //TH
	TS_write_byte(USER_BYTE_2); //TL
	TS_write_byte(DSCONFIG);
	TS_write_byte(Copy_Scratchpad);
}

int temp() // приём температуры
{
	unsigned char LS;
	unsigned int MS=0;
	if (TS_find()==1)
	{
		TS_write_byte(SKIP_ROM);
		TS_write_byte(CONVERT_T);
		_delay_ms(200);
		TS_find();
		TS_write_byte(SKIP_ROM);
		TS_write_byte(READ_SCRATCHPAD);
		LS=TS_read_byte();
		MS=TS_read_byte();
		MS=(MS<<8)|LS;
	}
	return MS;
}

char convert (unsigned int td)
{
	char dat=td>>4;//сдвиг и отсечение старшего байта
	return dat;// (знак,2в6,2в5,2в4,2в3,2в2,2в1,2в0)
}*/
#define SKIP_ROM         0xCC
#define CONVERT_T        0x44
#define READ_SCRATCHPAD  0xBE
#define Write_Scratchpad 0x4E
#define Copy_Scratchpad  0x48
#define USER_BYTE_1      0x7F
#define USER_BYTE_2      0xFF
#define DSCONFIG         0x3F


#define TS_DDR DDRB
#define TS_PORT PORTB
#define TS_PIN PINB
#define TS 7
#define TS_LOW TS_DDR |=1<<TS //0
#define TS_HIGH TS_DDR &=~(1<<TS)//1


char TS_find (void) // проверяем наличие датчика
{
	char SRO=SREG;
	cli();
	char device;
	TS_LOW;
	_delay_us(485);
	TS_HIGH;
	_delay_us(65);
	
	if((TS_PIN & (1<<TS))==0x00)
	{
		device=1;
		/*Uart_tr("OK \n");*/
	}
	
	else
	device=0;
	SREG=SRO;
	_delay_us(420);
	return device;
}

void TS_write_bit(char bit) // отправляем 1 бит на датчик
{
	char SR1=SREG;
	cli();
	TS_LOW;
	_delay_us(2);
	if(bit) TS_HIGH;
	_delay_us(65);
	TS_HIGH;
	SREG=SR1;
}

void TS_write_byte(unsigned char c) // отправляем 1 байт на датчик
{
	char i;
	for(i=0;i<8;i++)
	{
		if((c&(1<<i))== 1<<i)
		TS_write_bit(1);
		else
		TS_write_bit(0);
	}
}

char TS_read_bit (void) // считываем 1 бит с датчика
{
	char SR2=SREG;
	cli();
	char TS_bitm;
	TS_LOW;
	_delay_us(2);
	TS_HIGH;
	_delay_us(13);
	TS_bitm=(TS_PIN & (1<<TS))>>TS;
	_delay_us(45);
	SREG=SR2;
	return TS_bitm;
}

unsigned char TS_read_byte() // считывем 1 байт с датчика
{
	char data=0,i;
	for(i=0;i<8;i++)
	data |=TS_read_bit()<<i;
	return data;
}

void DS18B20_init ()
{
	TS_write_byte(SKIP_ROM);
	TS_write_byte(Write_Scratchpad);
	TS_write_byte(USER_BYTE_1); //TH
	TS_write_byte(USER_BYTE_2); //TL
	TS_write_byte(DSCONFIG);
	TS_write_byte(Copy_Scratchpad);
}

int temp() // приём температуры
{
	unsigned char LS;
	unsigned int MS=0;
	if (TS_find()==1)
	{
		TS_write_byte(SKIP_ROM);
		TS_write_byte(CONVERT_T);
		_delay_ms(200);
		TS_find();
		TS_write_byte(SKIP_ROM);
		TS_write_byte(READ_SCRATCHPAD);
		LS=TS_read_byte();
		MS=TS_read_byte();
		MS=(MS<<8)|LS;
	}
	return MS;
}

char convert (unsigned int td)
{
	char dat=td>>4;//сдвиг и отсечение старшего байтаzz
	return dat;// (знак,2в6,2в5,2в4,2в3,2в2,2в1,2в0)
}