
uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;
uint16_t dig_P1;
int16_t dig_P2;
int16_t dig_P3;
int16_t dig_P4;
int16_t dig_P5;
int16_t dig_P6;
int16_t dig_P7;
int16_t dig_P8;
int16_t dig_P9;
int32_t  t_fine;


#define BMP280_R 0xED
#define BMP280_W 0xEC

#define BMP280_REG_CONTROL 0xF4 // параметры сбора данных на устройстве
#define BMP280_REG_CONFIG 0xF5 // параметры скорости, фильтра и интерфейса устройства

#define BMP280_REG_RESULT_PRESSURE 0xF7 // 0xF7(msb) , 0xF8(lsb) , 0xF9(xlsb)
#define BMP280_REG_RESULT_TEMPRERATURE 0xFA // 0xFA(msb) , 0xFB(lsb) , 0xFC(xlsb) данные измерения необработанной температуры

#define BMP280_REGISTER_CHIPID 0xD0

#define BMP280_OVERSAMPLING_T1  0x20
#define BMP280_OVERSAMPLING_T2  0x40
#define BMP280_OVERSAMPLING_T4  0x60
#define BMP280_OVERSAMPLING_T8  0x80
#define BMP280_OVERSAMPLING_T16 0xA0

#define BMP280_OVERSAMPLING_P1  0x04
#define BMP280_OVERSAMPLING_P2  0x08
#define BMP280_OVERSAMPLING_P4  0x0C
#define BMP280_OVERSAMPLING_P8  0x10
#define BMP280_OVERSAMPLING_P16 0x14

#define BMP280_MODE_SLEEP  0x00
#define BMP280_MODE_FORCED 0x01
#define BMP280_MODE_NORMAL 0x03

#define BMP280_TSB_0_5  0x00
#define BMP280_TSB_62_5 0x20
#define BMP280_TSB_125  0x40
#define BMP280_TSB_250  0x60
#define BMP280_TSB_500  0x80
#define BMP280_TSB_1000 0xA0
#define BMP280_TSB_2000 0xC0
#define BMP280_TSB_4000 0xE0

#define BMP280_FILTER_OFF 0x00
#define BMP280_FILTER_COEFFICIENT2  0x04
#define BMP280_FILTER_COEFFICIENT4  0x08
#define BMP280_FILTER_COEFFICIENT8  0x0C
#define BMP280_FILTER_COEFFICIENT16 0x10

#define BMP280_SPI_OFF 0x00
#define BMP280_SPI_ON  0x01

#define BMP280_MEAS (BMP280_OVERSAMPLING_T16 | BMP280_OVERSAMPLING_P16 | BMP280_MODE_NORMAL)
#define BMP280_CONFIG (BMP280_TSB_125 | BMP280_FILTER_OFF | BMP280_SPI_OFF)

uint8_t bmp280Read8(uint8_t address)
{
	uint8_t data;
	i2c_start_cond();
	i2c_send_byte(BMP280_W); // write 0xEC
	i2c_send_byte(address); // write register address
	i2c_stop_cond();

	i2c_start_cond();
	i2c_send_byte(BMP280_R); // read 0xEF
	data = i2c_get_byte(1); // Get LSB result
	i2c_stop_cond();
	return data;
}

uint16_t bmp280ReadShort(uint8_t address)
{
	uint16_t msb=0;
	uint16_t lsb=0;
	uint16_t data;
	i2c_start_cond();
	i2c_send_byte(BMP280_W); // write 0xEE
	i2c_send_byte(address); // write register address
	i2c_stop_cond();
	
	i2c_start_cond();
	i2c_send_byte(BMP280_R); // read 0xEF
	lsb = i2c_get_byte(0);  // Get LSB result
	msb = i2c_get_byte(1); // Get MSB result
	i2c_stop_cond();
	data = (msb << 8) + lsb;
	return data;
}

uint32_t bmp280ReadLong(uint8_t address)
{
	uint32_t msb=0;
	uint32_t lsb=0;
	uint32_t xlsb=0;
	uint32_t data;
	i2c_start_cond();
	i2c_send_byte(BMP280_W); // write 0xEE
	i2c_send_byte(address); // write register address
	i2c_stop_cond();

	i2c_start_cond();
	i2c_send_byte(BMP280_R);  // read 0xEF
	msb = i2c_get_byte(0);   // Get MSB result
	lsb = i2c_get_byte(0);  // Get LSB result
	xlsb = i2c_get_byte(1);// Get XLSB result
	i2c_stop_cond();
	
	data = ((msb << 16) + (lsb << 8) + xlsb) >> 4;
	return data;
}

void bmp280WriteByte(uint8_t address, uint8_t data)
{
	i2c_start_cond();
	i2c_send_byte(BMP280_W); // write 0xEE
	i2c_send_byte(address); // Register Address
	i2c_send_byte(data);   // Data
	i2c_stop_cond();
}

int32_t read_T(void)
{
	int32_t adc_T=bmp280ReadLong(BMP280_REG_RESULT_TEMPRERATURE);
	int32_t var1, var2, T;
	var1 = ((((adc_T>>3)
	-((int32_t)dig_T1<<1))) * ((int32_t)dig_T2))>>11;
	var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) -((int32_t)dig_T1)))>>12) * ((int32_t)dig_T3))>>14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

uint32_t read_P(void)
{
	int32_t adc_P = bmp280ReadLong(BMP280_REG_RESULT_PRESSURE);
	int32_t var1, var2;
	uint32_t p;
	var1 = (((int32_t )t_fine)>>1) - (int32_t )64000;
	var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t )dig_P6);
	var2 = var2 + ((var1*((int32_t )dig_P5))<<1);
	var2 = (var2>>2)+(((int32_t )dig_P4)<<16);
	var1 = (((dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t )dig_P2) * var1)>>1))>>18;
	var1 =((((32768+var1))*((int32_t )dig_P1))>>15);
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = (((uint32_t )(((int32_t )1048576)-adc_P)-(var2>>12)))*3125;
	if (p < 0x80000000)
	{
		p = (p << 1) / ((uint32_t )var1);
	}
	else
	{
		p = (p / (uint32_t )var1) * 2;
	}
	var1 = (((int32_t )dig_P9) * ((int32_t )(((p>>3) * (p>>3))>>13)))>>12;
	var2 = (((int32_t )(p>>2)) * ((int32_t )dig_P8))>>13;
	p = (uint32_t )((int32_t )p + ((var1 + var2 + dig_P7) >> 4));
	return p;
}

void BMP280_Begin()
{
	/*if (bmp280Read8(BMP280_REGISTER_CHIPID) != 0x58)
	{
		Uart_tr("BMP280_FALSE\n");
	}
	else
	{
		Uart_tr("BMP280_READY\n");
	}*/
	dig_T1 = bmp280ReadShort(0x88);
	dig_T2 = bmp280ReadShort(0x8A);
	dig_T3 = bmp280ReadShort(0x8C);
	dig_P1 = bmp280ReadShort(0x8E);
	dig_P2 = bmp280ReadShort(0x90);
	dig_P3 = bmp280ReadShort(0x92);
	dig_P4 = bmp280ReadShort(0x94);
	dig_P5 = bmp280ReadShort(0x96);
	dig_P6 = bmp280ReadShort(0x98);
	dig_P7 = bmp280ReadShort(0x9A);
	dig_P8 = bmp280ReadShort(0x9C);
	dig_P9 = bmp280ReadShort(0x9E);

	bmp280WriteByte(BMP280_REG_CONFIG, BMP280_CONFIG);
	bmp280WriteByte(BMP280_REG_CONTROL, BMP280_MEAS);
}
