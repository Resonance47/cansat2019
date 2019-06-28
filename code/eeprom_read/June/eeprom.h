#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_write_1byte(unsigned int adress, uint8_t data)
{
	while(EECR & (1 << EEWE));
	EEAR = adress;
	EEDR = data;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);
}

uint8_t EEPROM_read_1byte(unsigned int adress)
{
	while(EECR & (1 << EEWE));
	EEAR = adress;
	EECR |= (1 << EERE);
	return EEDR;
}

void EEPROM_write_2byte(unsigned int adress, uint16_t data)
{
	EEPROM_write_1byte(adress, (uint8_t) data);
	EEPROM_write_1byte(adress + 1, (uint8_t) (data >> 8));
}

uint16_t EEPROM_read_2byte(unsigned int adress)
{
	uint16_t data = EEPROM_read_1byte(adress + 1) << 8;
	asm("nop");
	data += EEPROM_read_1byte(adress);
	return data;
}

void EEPROM_write_4byte(unsigned int adress, uint32_t data)
{
	EEPROM_write_1byte(adress, (uint8_t)(data >> 24));
	EEPROM_write_1byte(adress+1, (uint8_t)(data >> 16));
	EEPROM_write_1byte(adress+2, (uint8_t)(data >> 8));
	EEPROM_write_1byte(adress+3, (uint8_t)(data));
}

uint32_t EEPROM_read_4byte(unsigned int adress)
{
	return ( ((uint32_t)(EEPROM_read_1byte(adress)) << 24) | ((uint32_t)(EEPROM_read_1byte(adress+1)) << 16) | ((uint32_t)(EEPROM_read_1byte(adress+2)) << 8) | ((uint32_t)(EEPROM_read_1byte(adress+3))) );
}

void EEPROM_write_string(unsigned int adress, char str[])
{
	for(int i=0; str[i] != '\0'; i++)
		EEPROM_write_1byte(adress + i, (unsigned char) str[i]);
}

unsigned char* EEPROM_read_string(unsigned int adress, unsigned int length)
{
	unsigned char *str = (unsigned char *) malloc(length);
	for(int i=0; i < length; i++)
		str[i] = EEPROM_read_1byte(adress + i);
	return str;
}

void eepromread()
{
	char EE[15];
	for(uint64_t i=0; i<4096; i+=16)
	{
		sprintf(EE, "%d;", EEPROM_read_2byte(i)); uart_tr_string(EE);
		sprintf(EE, "%d;", EEPROM_read_2byte(i+2)); uart_tr_string(EE);
		sprintf(EE, "%d;", EEPROM_read_2byte(i+4)); uart_tr_string(EE);
		sprintf(EE, "%d;", EEPROM_read_2byte(i+6)); uart_tr_string(EE);
		sprintf(EE, "%ld;", EEPROM_read_4byte(i+8)); uart_tr_string(EE);
		sprintf(EE, "%ld;\n", EEPROM_read_4byte(i+12)); uart_tr_string(EE);
	}
}



#endif /* EEPROM_H_ */