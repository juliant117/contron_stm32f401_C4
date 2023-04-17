#include "stm32f4xx.h"
#include <string.h>

#include "mpu6050_1.h"

using namespace std;

MPU6050_1::MPU6050_1(){}   //constructor
	

void MPU6050_1::mpu_write(int16_t mpu_addr,int16_t reg,int16_t data){
	//write data to mpu6050  single byte
	Start_i2c();
	ev5_i2c();
	addres_transmit_i2c(mpu_addr);
	ev6_i2c();
	ev8_1_i2c();
	write_i2c(reg);
	ev8_i2c();
	write_i2c(data);
	ev8_2_i2c();
	stop_i2c();
}
int MPU6050_1::mpu_read(int16_t mpu_addr,int16_t reg){
	int8_t data;
	//read data from mpu6050  single byte
	Start_i2c();
	ev5_i2c();
	addres_transmit_i2c(mpu_addr);
	ev6_i2c();
	
	ev8_i2c();
	write_i2c(reg);
	ev8_2_i2c();
	
	//** como que falta reciir el acknoledge
	Start_i2c();
	ev5_i2c();

	addres_recive_i2c(mpu_addr);
	ev6_i2c();
	set_aknowledge(0);			// ACK: Acknowledge disable
	
	ev7_i2c();
  data=read_i2c();
	
	stop_i2c();
	return data;
}
	
void MPU6050_1::set_init(){
	//set default settings
	//sttings
	mpu_write(0x68,CONFIG,0x00);
	//GYRO_CONFIG
	mpu_write(0x68,GYRO_CONFIG,0x00);
	//ACCEL_CONFIG
	mpu_write(0x68,ACCEL_CONFIG,0x00);
	
}

//void MPU6050_1::set_init(){
//	//set default settings
//	//sttings
//	mpu_write(0x68,CONFIG,0x00);
//	//GYRO_CONFIG
//	mpu_write(0x68,GYRO_CONFIG,0x00);
//	//ACCEL_CONFIG
//	mpu_write(0x68,ACCEL_CONFIG,0x00);
//	
//}
	
