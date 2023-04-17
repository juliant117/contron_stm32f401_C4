#include "stm32f4xx.h"

#include "mpu6050_1.h"



MPU6050_1::MPU6050_1(){}   //constructor
	
//********************** dafault algorithm   ********************************
void MPU6050_1::mpu_write(int16_t reg,int16_t data){
	//write data to mpu6050  single byte
	Start_i2c();
	ev5_i2c();
	addres_transmit_i2c(MPU6050_ADDR);
	ev6_i2c();
	ev8_1_i2c();
	write_i2c(reg);
	ev8_i2c();
	write_i2c(data);
	ev8_2_i2c();
	stop_i2c();
}
int MPU6050_1::mpu_read(int16_t reg){
	int8_t data;
	//read data from mpu6050  single byte
	Start_i2c();
	ev5_i2c();
	addres_transmit_i2c(MPU6050_ADDR);
	ev6_i2c();
	
	ev8_i2c();
	write_i2c(reg);
	ev8_2_i2c();
	
	//** como que falta reciir el acknoledge
	Start_i2c();
	ev5_i2c();

	addres_recive_i2c(MPU6050_ADDR);
	ev6_i2c();
	set_aknowledge(0);			// ACK: Acknowledge disable
	
	ev7_i2c();
  data=read_i2c();
	
	stop_i2c();
	return data;
}
//********************** mpu6050 settings   ********************************
void MPU6050_1::set_ADDR(bool addr){
	//modify default addr  
	//this is for AD0 pin with 1 or 0
	if(addr){
	this->MPU6050_ADDR=0x69;     //AD0=1
	}
	else{
	this->MPU6050_ADDR=0x68;		//AD0=0
	}
	

}
	
void MPU6050_1::set_init(){
	//set default settings
	//sttings
	//mpu_write(0x68,CONFIG,0x00);
	//GYRO_CONFIG
	
	mpu_write(GYRO_CONFIG,0x00);
	//ACCEL_CONFIG
	mpu_write(ACCEL_CONFIG,0x00);
	
}
//********************** mpu6050 read   ********************************

int MPU6050_1::read_data(int index){
	int datain[2];

	//just for now gyro +-250°/s
	////just for now accel +-2g
	//Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 36.53
	
	switch(index)
	{
		case 1:
		datain[0]=mpu_read(ACCEL_XOUT_H);
		datain[1]=mpu_read(ACCEL_XOUT_L);
		data_mpu=datain[0]<<8 | datain[1];	
		break;
		case 2:
		datain[0]=mpu_read(TEMP_OUT_H);
		datain[1]=mpu_read(TEMP_OUT_L);
		data_mpu=datain[0]<<8 | datain[1];
		break;
		case 3:
		datain[0]=mpu_read(GYRO_XOUT_H);
		datain[1]=mpu_read(GYRO_XOUT_L);
		data_mpu=datain[0]<<8 | datain[1];
		break;
	}
	
	return data_mpu;
}
	
