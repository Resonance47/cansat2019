#define si_R 0x81
#define si_W 0x80
#define temp_si 0xE3
#define humidity 0xE5
#define chipID 0x15


uint16_t siReadShort(uint8_t address)
{
	uint16_t msb=0;
	uint16_t lsb=0;
	uint16_t data;
	i2c_start_cond1();
	i2c_send_byte1(si_W);
	i2c_send_byte1(address);
	i2c_stop_cond1();
	
	_delay_ms(100); ///why this one?
	
	i2c_start_cond1();
	i2c_send_byte1(si_R);

	msb = i2c_get_byte1(0);
	lsb = i2c_get_byte1(1);
	i2c_stop_cond1();
	data = (msb << 8) + lsb;
	return data;
}

int si_read_T()
{
	int lowT = siReadShort(0xE3);
	int highT = ((172.75*lowT)/65536)-46.85;
	return highT;
}
int si_read_h()
{
	double lowH = siReadShort(0xE5);
	int highW = int(125*lowH/65536)-6;//all right(DATASEET check)
	return highW;
}

// void si7021check()
// {
// 	uint8_t data;
// 	i2c_start_cond1();
// 	i2c_send_byte1(si_W);
// 	i2c_send_byte1(0xFC);
// 	i2c_send_byte1(0xC9);
// 	i2c_stop_cond1();
// 
// 	i2c_start_cond1();
// 	i2c_send_byte1(si_R);
// 	data = i2c_get_byte1(1);
// 	i2c_stop_cond1();
// // 	if(data == 0x32)
// // 		Uart_tr("SiREADY");
// // 	else
// // 		Uart_tr("SiFALSE");
// }
