#include "stm32f4xx.h"
#include "I2c_own_1.h"

#ifndef MPU6050_1_H
#define MPU6050_1_H

class MPU6050_1:public I2c_own_1
{	
	private:
	int32_t MPU6050_ADDR =0x68;
	int32_t SELF_TEST_X =0x0D; 
	int32_t SELF_TEST_Y =0x0E; 
	int32_t SELF_TEST_Z =0x0F;
	int32_t SELF_TEST_A =0x10;  
	int32_t CONFIG  =0x1A;
	int32_t	GYRO_CONFIG =0x1B;
	int32_t ACCEL_CONFIG =0x1C;
	int32_t	ACCEL_XOUT_H =0x3B; 
	int32_t ACCEL_XOUT_L =0x3C;
	int32_t	ACCEL_YOUT_H =0x3D;
	int32_t ACCEL_YOUT_L =0x3E;
	int32_t	ACCEL_ZOUT_H =0x3F;
	int32_t ACCEL_ZOUT_L =0x40;
	int32_t	TEMP_OUT_H =0x41;
	int32_t TEMP_OUT_L =0x42;

	int32_t GYRO_XOUT_H =0x43;
	int32_t	GYRO_XOUT_L =0x44;
	int32_t GYRO_YOUT_H =0x45;
	int32_t GYRO_YOUT_L =0x46;
	int32_t	GYRO_ZOUT_H =0x47;
	int32_t GYRO_ZOUT_L =0x48;
	
	
	public:	
	MPU6050_1();
	~MPU6050_1(){};
		
	I2c_own_1 mpu6050_s1; 
	
	void mpu_write(int16_t mpu_addr,int16_t reg,int16_t data);
	int mpu_read(int16_t mpu_addr,int16_t reg);
	
	void set_init();


	
		
};
#endif