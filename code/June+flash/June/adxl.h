int32_t temperature = 0;
uint32_t pressure = 0;
int32_t altitude = 0;
int32_t temperature_1 = 0;
int32_t    pressure_1 = 0;
int32_t Tt;


unsigned char ACCEL_xh;
unsigned char ACCEL_xl;
unsigned char ACCEL_yh;
unsigned char ACCEL_yl;
unsigned char ACCEL_zh;
unsigned char ACCEL_zl;

long int ACCEL_X;
long int ACCEL_Y;
long int ACCEL_Z;

long int ACCEL_XANGLE;
long int ACCEL_YANGLE;
long int ACCEL_ZANGLE;

unsigned char ID;

#define ADXL_R 0b10100111
#define ADXL_W 0b10100110

void I2C_write (unsigned char reg, unsigned char value) 
{

	i2c_start_cond();
	i2c_send_byte(ADXL_W);
	i2c_send_byte(reg);
	i2c_send_byte(value);
	i2c_stop_cond();

}

void Init_ADXL (void)
{
	I2C_write (0x2D, 0x28);
	I2C_write (0x31, 0x03);
	I2C_write (0x38, 0x00);
} 
void GET_ACCEL () 
{

	i2c_start_cond();
	i2c_send_byte(ADXL_W);
	i2c_send_byte(0x32);
	i2c_stop_cond();

	i2c_start_cond();
	i2c_send_byte(ADXL_R);
	ACCEL_xl = i2c_get_byte(0);
	ACCEL_xh = i2c_get_byte(0);
	ACCEL_yl = i2c_get_byte(0);
	ACCEL_yh = i2c_get_byte(0);
	ACCEL_zl = i2c_get_byte(0);
	ACCEL_zh = i2c_get_byte(1);
	i2c_stop_cond();

	ACCEL_X = 31.2*(ACCEL_xh*256 + ACCEL_xl)-54;
	ACCEL_Y = 31.2*(ACCEL_yh*256 + ACCEL_yl)-56;
	ACCEL_Z = 31.2*(ACCEL_zh*256 + ACCEL_zl)-23;
}

void GET_ID ()
{
	i2c_start_cond();
	i2c_send_byte(ADXL_W);
	i2c_send_byte(0x00);
	i2c_stop_cond();
	i2c_start_cond();
	i2c_send_byte(ADXL_R);
	ID = i2c_get_byte(1);
	i2c_stop_cond();
}

char read_bit (void)
{
	char SR2=SREG;
	cli();
	char bit;
	DDRB |=1<<7;
	_delay_us(2);
	DDRB &=~(1<<7);
	_delay_us(13);
	bit=(PINB & (1<<7))>>7;
	_delay_us(45);
	SREG=SR2;
	return bit;
}

