#define w 0b11010000
#define r 0b11010001
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define check 0x75
#define chipid 0x71
#define CONFIG2 0x1A

#define X 0x3B
#define Y 0x3D
#define Z 0x3F


#define GX 0x43
#define GY 0x45
#define GZ 0x47

int16_t mpuReadShort (uint8_t reg)
{
	int16_t msb=0;
	int16_t lsb=0;
	int16_t data=0;

	i2c_start_cond1();
	i2c_send_byte1(w);
	i2c_send_byte1(reg);
	i2c_stop_cond1();

	i2c_start_cond1();
	i2c_send_byte1(r);
	msb=i2c_get_byte1(0);
	lsb=i2c_get_byte1(1);
	i2c_stop_cond1();
	data = (msb << 8) + lsb;
	return data;


}

void write_reg (uint8_t reg, uint8_t data)
{
	
	i2c_start_cond1();
	i2c_send_byte1(w);
	i2c_send_byte1(reg);
	i2c_send_byte1(data);
	i2c_stop_cond1();
}

uint8_t read_reg_8 (uint8_t reg)
{
	uint8_t data;
	i2c_start_cond1();
	i2c_send_byte1(w);
	i2c_send_byte1(check);
	i2c_stop_cond1();

	i2c_start_cond1();
	i2c_send_byte1(r);

	data = i2c_get_byte1(1);
	i2c_stop_cond1();
	return data;

}
void mpu9250check()
{

	if (read_reg_8(check) != chipid)
	{
		//Uart_tr("mpuFALSE\n");
	}

	else
	{
		//Uart_tr("mpuREADY\n");
	}
	write_reg(ACCEL_CONFIG, 0b00001000);
}


class read//класс прербразований значений
{
public:
//////////////////////////////////
//TODO: матрица напр косинусов
/////////////////////////////////
	int mpu_read_Ax()
	{
		int lowX = 9.82/10*(mpuReadShort(X)/8.192);
		return lowX;
	};
	int mpu_read_Ay()
	{
		int lowY = 9.82/10*(mpuReadShort(Y)/8.192);
		return lowY;
	};
	int mpu_read_Az()
	{
		int lowZ = 9.82/10*(mpuReadShort(Z)/8.192);
		return lowZ;
	};


	int mpu_read_hyroX()
	{
		int lowGX = int(mpuReadShort(GX))/131;
		return lowGX;
	};
	
	int mpu_read_hyroY()
	{
		int lowGY = int(mpuReadShort(GY))/131;
		return lowGY;
	};
	int mpu_read_hyroZ()
	{
		int lowGZ = int(mpuReadShort(GZ))/131;
		return lowGZ;
	};
};