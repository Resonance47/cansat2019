#ifndef FLASH_W25Q_H_
#define FLASH_W25Q_H_

////////////////////////////////////////////////// Settings

//CS_FLASH
#define CS_FLASH_DDR DDRE
#define CS_FLASH_PORT PORTE
#define CS_FLASH 6

#define FLASH_DELAY _delay_ms(1)


////////////////////////////////////////////////// Flash Instructions

#define WRITE_ENABLE 0x06
#define WRITE_DISABLE 0x04
#define CHIP_ERACE 0x60
#define SECTOR_ERACE 0x20
#define READ_STATUS_REGISTER1 0x05
#define PAGE_PROGRAM 0x02
#define READ_DATA 0x03


////////////////////////////////////////////////// Functions

void flash_start()
{
	CS_FLASH_PORT &= ~(1 << CS_FLASH);
}

void flash_stop()
{
	CS_FLASH_PORT |= (1 << CS_FLASH);
}

void flash_init()
{
	CS_FLASH_DDR |= (1 << CS_FLASH);
	flash_stop();
}

// занята ли микросхема какой-либо операцией
bool is_flash_busy()
{
	uint8_t data;
	flash_start();
	
	spi_write_byte(READ_STATUS_REGISTER1);
	data = spi_read_byte();
	
	flash_stop();
	FLASH_DELAY;
	
	if(data & 0b00000001)
	return true;
	else
	return false;
}

void flash_write_enable()
{
	while(is_flash_busy());
	flash_start();
	spi_write_byte(WRITE_ENABLE);
	flash_stop();
	FLASH_DELAY;
}

void flash_write_disable()
{
	while(is_flash_busy());
	flash_start();
	spi_write_byte(WRITE_DISABLE);
	flash_stop();
	FLASH_DELAY;
}

// полная очистка
void flash_chip_erase()
{
	flash_write_enable();
	flash_start();
	spi_write_byte(CHIP_ERACE);
	flash_stop();
	FLASH_DELAY;
}

void flash_sector_erace_4kb(uint32_t addr)
{
	flash_write_enable();
	flash_start();
	spi_write_byte(SECTOR_ERACE);
	spi_write_byte((uint8_t)(addr >> 16));
	spi_write_byte((uint8_t)(addr >> 8));
	spi_write_byte((uint8_t)addr);
	flash_stop();
	FLASH_DELAY;
}

void flash_write_1byte(uint32_t addr, uint8_t data)
{
	flash_write_enable();
	FLASH_DELAY;
	flash_start();
	
	spi_write_byte(PAGE_PROGRAM);
	spi_write_byte((uint8_t)(addr >> 16));
	spi_write_byte((uint8_t)(addr >> 8));
	spi_write_byte((uint8_t)addr);
	spi_write_byte(data);
	
	flash_stop();
	FLASH_DELAY;
}

uint8_t flash_read_1byte(uint32_t addr)
{
	uint8_t data;
	while(is_flash_busy());
	
	flash_start();
	spi_write_byte(READ_DATA);
	spi_write_byte((uint8_t)(addr >> 16));
	spi_write_byte((uint8_t)(addr >> 8));
	spi_write_byte((uint8_t)addr);
	data = spi_read_byte();
	flash_stop();
	
	FLASH_DELAY;
	return data;
}


int m;
// int puck = 0;
// void contin(int c)
// {
// 	m = c;
// }
// void flash_write_string(char u[120])
// {
// 	int mumm = 0;
// 	while (1)
// 	{
// 		if(mumm = 120)
// 			break;
// 		if(u[mumm] = '\0')
// 			break;
// 		mumm++;
// 	}
// 	double *FLEXX;
// 	FLEXX = new double[mumm-1];
// 	
// 	for(int i=0; i < puck; i++)
// 		flash_write_1byte(puck + i, FLEXX[i]);
// 	puck+=mumm;
// }

void uart_tr_char(char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}
// 
// void flash_read_string()
// {
// 	for(int i=0; i < 16000; i++)
// 	{
//  		uart_tr_char(flash_read_1byte(i));
// //  		if(i%50 == 0)
// // 		 {
// //  			uart_tr_char('\n');
// // 			uart_tr_char('\n');
// // 			uart_tr_char('\n');
// // 		 }
// 	}
// }
void uart_tr_string(const char *str)
{
	for(int i=0; str[i] != '\0'; i++)
	{
		uart_tr_char(str[i]);
	}
}

void uart_tr_int(long int data_in)
{
	if(data_in < 0)
	uart_tr_char('-');

	data_in = labs(data_in);
	long int data_in_buff = data_in;
	long int count = 1;

	while(data_in_buff >= 10)
	{
		count *= 10;
		data_in_buff /= 10;
	}

	for(long int i=1; i <= count; i *= 10)
	{
		uart_tr_char(((char)(data_in / (count / i))) + 0x30);
		data_in %= count / i;
	}
}

uint32_t num_pack_addr = 0;
// void flashwrite(uint32_t num_pack, int x, int y, int z, int temp, int hum, int high, int v, uint32_t lat, uint32_t lon/*рез-т работы доп мисии*/, uint32_t relat, uint32_t relon /*настоящие координаты*/, uint16_t vero1, uint16_t vero2, uint16_t vero3, uint16_t vero4)
// {
// 	if(num_pack > 0)
// 	{
// 		if(num_pack != 1 && (num_pack) % 6 == 0)
// 		{
// 			uart_tr_string("+28\n");
// 			num_pack_addr += 28;
// 		}
// 		else
// 			num_pack_addr += 38;
// 	}
// 	
// 	uart_tr_int(num_pack); uart_tr_char(' ');
// 	uart_tr_int(num_pack_addr); uart_tr_string ("\n");
// 	
// 	flash_write_enable();
// 	FLASH_DELAY;
// 	flash_start();
// 	
// 	spi_write_byte(PAGE_PROGRAM);
// 	spi_write_byte((uint8_t)(num_pack_addr >> 16));
// 	spi_write_byte((uint8_t)(num_pack_addr >> 8));
// 	spi_write_byte((uint8_t)num_pack_addr);
// 	
// 	spi_write_byte((uint8_t)(x >> 8)); spi_write_byte((uint8_t)x);
// 	spi_write_byte((uint8_t)(y >> 8)); spi_write_byte((uint8_t)y);
// 	spi_write_byte((uint8_t)(z >> 8)); spi_write_byte((uint8_t)z);
// 	
// 	spi_write_byte((uint8_t)(temp >> 8)); spi_write_byte((uint8_t)temp);
// 	spi_write_byte((uint8_t)(hum >> 8)); spi_write_byte((uint8_t)hum);
// 	
// 	spi_write_byte((uint8_t)(high >> 8)); spi_write_byte((uint8_t)high);
// 	spi_write_byte((uint8_t)(v >> 8)); spi_write_byte((uint8_t)v);
// 	
// 	spi_write_byte((uint8_t)(lat >> 24)); spi_write_byte((uint8_t)(lat >> 16));  spi_write_byte((uint8_t)(lat >> 8));  spi_write_byte((uint8_t)lat);
// 	spi_write_byte((uint8_t)(lon >> 24)); spi_write_byte((uint8_t)(lon >> 16));  spi_write_byte((uint8_t)(lon >> 8));  spi_write_byte((uint8_t)lon);
// 	spi_write_byte((uint8_t)(relat >> 24)); spi_write_byte((uint8_t)(relat >> 16));  spi_write_byte((uint8_t)(relat >> 8));  spi_write_byte((uint8_t)relat);
// 	spi_write_byte((uint8_t)(relon >> 24)); spi_write_byte((uint8_t)(relon >> 16));  spi_write_byte((uint8_t)(relon >> 8));  spi_write_byte((uint8_t)relon);
// 	
// 	spi_write_byte((uint8_t)(vero1 >> 8)); spi_write_byte((uint8_t)vero1);
// 	spi_write_byte((uint8_t)(vero2 >> 8)); spi_write_byte((uint8_t)vero2);
// 	spi_write_byte((uint8_t)(vero3 >> 8)); spi_write_byte((uint8_t)vero3);
// 	spi_write_byte((uint8_t)(vero4 >> 8)); spi_write_byte((uint8_t)vero4);
// 	
// 	flash_stop();
// 	FLASH_DELAY;
// }
// 
// void flashread()
// {
// 	char FA[20];
// 	
// 	for(uint64_t i=0; i < 16777216; i += 256)
// 	{
// 		while(is_flash_busy());
// 	
// 		flash_start();
// 		spi_write_byte(READ_DATA);
// 		spi_write_byte((uint8_t)(i >> 16));
// 		spi_write_byte((uint8_t)(i >> 8));
// 		spi_write_byte((uint8_t)i);
// 		
// 		for(uint16_t j=0; j<6; j+=1)
// 		{
// 		
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte()) << 8) | (int)spi_read_byte()) ); uart_tr_string(FA);
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte()) << 8) | (int)spi_read_byte()) ); uart_tr_string(FA);
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte()) << 8) | (int)spi_read_byte()) ); uart_tr_string(FA);
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte()) << 8) | (int)spi_read_byte()) ); uart_tr_string(FA);
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte()) << 8) | (int)spi_read_byte()) ); uart_tr_string(FA);
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte()) << 8) | (int)spi_read_byte()) ); uart_tr_string(FA);
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte()) << 8) | (int)spi_read_byte()) ); uart_tr_string(FA);
// 		
// 			sprintf(FA, "%ld;", (((uint32_t)(spi_read_byte()))<<24) | (((uint32_t)(spi_read_byte()))<<16) | (((uint32_t)(spi_read_byte()))<<8) | ((uint32_t)(spi_read_byte()))); uart_tr_string(FA);
// 			sprintf(FA, "%ld;", (((uint32_t)(spi_read_byte()))<<24) | (((uint32_t)(spi_read_byte()))<<16) | (((uint32_t)(spi_read_byte()))<<8) | ((uint32_t)(spi_read_byte()))); uart_tr_string(FA);
// 			sprintf(FA, "%ld;", (((uint32_t)(spi_read_byte()))<<24) | (((uint32_t)(spi_read_byte()))<<16) | (((uint32_t)(spi_read_byte()))<<8) | ((uint32_t)(spi_read_byte()))); uart_tr_string(FA);
// 			sprintf(FA, "%ld;", (((uint32_t)(spi_read_byte()))<<24) | (((uint32_t)(spi_read_byte()))<<16) | (((uint32_t)(spi_read_byte()))<<8) | ((uint32_t)(spi_read_byte()))); uart_tr_string(FA);
// 		
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte() ) << 8) | (int)spi_read_byte() ) ); uart_tr_string(FA);
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte() ) << 8) | (int)spi_read_byte() ) ); uart_tr_string(FA);
// 			sprintf(FA, "%d;", ( ( ( (int)spi_read_byte() ) << 8) | (int)spi_read_byte() ) ); uart_tr_string(FA);
// 			sprintf(FA, "%d;\n", ( ( ( (int)spi_read_byte() ) << 8) | (int)spi_read_byte() ) ); uart_tr_string(FA);
// 
// 		}
// 		flash_stop();
// 		FLASH_DELAY;
// 		_delay_ms(200);
// 	}
// }








void flashwrite(uint32_t num_pack, int x, int y, int z, int temp, int hum, int high, int v, uint32_t lat, uint32_t lon/*рез-т работы доп мисии*/, uint32_t relat, uint32_t relon /*настоящие координаты*/, uint16_t vero1, uint16_t vero2, uint16_t vero3, uint16_t vero4)
{
	num_pack*=38;
	flash_write_1byte(num_pack, (uint8_t)(x >> 8)); flash_write_1byte(num_pack+1, (uint8_t)x);
	flash_write_1byte(num_pack+2, (uint8_t)(y >> 8)); flash_write_1byte(num_pack+3, (uint8_t)y);
	flash_write_1byte(num_pack+4, (uint8_t)(z >> 8)); flash_write_1byte(num_pack+5, (uint8_t)z);
	
	flash_write_1byte(num_pack+6, (uint8_t)(temp >> 8)); flash_write_1byte(num_pack+7, (uint8_t)temp);
	flash_write_1byte(num_pack+8, (uint8_t)(hum >> 8)); flash_write_1byte(num_pack+9, (uint8_t)hum);
	
	flash_write_1byte(num_pack+10, (uint8_t)(high >> 8)); flash_write_1byte(num_pack+11, (uint8_t)high);
	flash_write_1byte(num_pack+12, (uint8_t)(v >> 8)); flash_write_1byte(num_pack+13, (uint8_t)v);
	
	flash_write_1byte(num_pack+14, (uint8_t)(lat >> 24)); flash_write_1byte(num_pack+15, (uint8_t)(lat >> 16));  flash_write_1byte(num_pack+16, (uint8_t)(lat >> 8));  flash_write_1byte(num_pack+17, (uint8_t)lat);
	flash_write_1byte(num_pack+18, (uint8_t)(lon >> 24)); flash_write_1byte(num_pack+19, (uint8_t)(lon >> 16));  flash_write_1byte(num_pack+20, (uint8_t)(lon >> 8));  flash_write_1byte(num_pack+21, (uint8_t)lon);
	flash_write_1byte(num_pack+22, (uint8_t)(relat >> 24)); flash_write_1byte(num_pack+23, (uint8_t)(relat >> 16));  flash_write_1byte(num_pack+24, (uint8_t)(relat >> 8));  flash_write_1byte(num_pack+25, (uint8_t)relat);
	flash_write_1byte(num_pack+26, (uint8_t)(relon >> 24)); flash_write_1byte(num_pack+27, (uint8_t)(relon >> 16));  flash_write_1byte(num_pack+28, (uint8_t)(relon >> 8));  flash_write_1byte(num_pack+29, (uint8_t)relon);
	
	flash_write_1byte(num_pack+30, (uint8_t)(vero1 >> 8)); flash_write_1byte(num_pack+31, (uint8_t)vero1);
	flash_write_1byte(num_pack+32, (uint8_t)(vero2 >> 8)); flash_write_1byte(num_pack+33, (uint8_t)vero2);
	flash_write_1byte(num_pack+34, (uint8_t)(vero3 >> 8)); flash_write_1byte(num_pack+35, (uint8_t)vero3);
	flash_write_1byte(num_pack+36, (uint8_t)(vero4 >> 8)); flash_write_1byte(num_pack+37, (uint8_t)vero4);
}

void flashread()
{
	char FA[10];
	for(uint64_t i(0); i<16777216; i+=38)
	///for(uint64_t i(0); i<76; i+=38)
	{
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i) ) << 8) | ((int)flash_read_1byte(i+1) ) )); uart_tr_string(FA);
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i+2) ) << 8) | ((int)flash_read_1byte(i+3) ) )); uart_tr_string(FA);
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i+4) ) << 8) | ((int)flash_read_1byte(i+5) ) )); uart_tr_string(FA);
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i+6) ) << 8) | ((int)flash_read_1byte(i+7) )) ); uart_tr_string(FA);
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i+8) ) << 8) | ((int)flash_read_1byte(i+9) ) )); uart_tr_string(FA);
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i+10) ) << 8) | ((int)flash_read_1byte(i+11) )) ); uart_tr_string(FA);
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i+12) ) << 8) |((int)flash_read_1byte(i+13) ) )); uart_tr_string(FA);
		
		sprintf(FA, "%ld;", (((uint32_t)(flash_read_1byte(i+14)))<<24) | (((uint32_t)(flash_read_1byte(i+15)))<<16) | (((uint32_t)(flash_read_1byte(i+16)))<<8) | ((uint32_t)(flash_read_1byte(i+17)))); uart_tr_string(FA);
		sprintf(FA, "%ld;", (((uint32_t)(flash_read_1byte(i+18)))<<24) | (((uint32_t)(flash_read_1byte(i+19)))<<16) | (((uint32_t)(flash_read_1byte(i+20)))<<8) | ((uint32_t)(flash_read_1byte(i+21)))); uart_tr_string(FA);
		sprintf(FA, "%ld;", (((uint32_t)(flash_read_1byte(i+22)))<<24) | (((uint32_t)(flash_read_1byte(i+23)))<<16) | (((uint32_t)(flash_read_1byte(i+24)))<<8) | ((uint32_t)(flash_read_1byte(i+25)))); uart_tr_string(FA);
		sprintf(FA, "%ld;", (((uint32_t)(flash_read_1byte(i+26)))<<24) | (((uint32_t)(flash_read_1byte(i+27)))<<16) | (((uint32_t)(flash_read_1byte(i+28)))<<8) | ((uint32_t)(flash_read_1byte(i+29)))); uart_tr_string(FA);
		
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i+30) ) << 8) | ((int)flash_read_1byte(i+31) ) )); uart_tr_string(FA);
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i+32) ) << 8) | ((int)flash_read_1byte(i+33) ) )); uart_tr_string(FA);
		sprintf(FA, "%d;", ( ( ( (int)flash_read_1byte(i+34) ) << 8) | ((int)flash_read_1byte(i+35) ) )); uart_tr_string(FA);
		sprintf(FA, "%d;\n", ( ( ( (int)flash_read_1byte(i+36) ) << 8) | ((int)flash_read_1byte(i+37) )) ); uart_tr_string(FA);
	}
}







#endif /* FLASH_W25Q_H_ */