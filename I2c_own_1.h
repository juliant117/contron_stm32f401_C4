#include "stm32f4xx.h"

#include "GP_M_1.h"



#ifndef I2c_own_1_H
#define	I2c_own_1_H

class I2c_own_1:public GPIO_own_1{
public:
	I2c_own_1();
	~I2c_own_1(){};
	//***************** own subclasses *****************
	GPIO_own_1 own_scl;
	GPIO_own_1 own_sda;	
		
	I2C_TypeDef * i2c_n;	
		
void set_i2c_n(int i2c_n_in,int freq_i2c, int clokfreq);				//i2c setting
		
void set_i2c_scl(int pin, char bus,int afr);
void set_i2c_sda(int pin, char bus,int afr);		
		
//***************** i2c event stream *****************
void addres_transmit_i2c(uint8_t addr_s);							//i2c sen data
void addres_recive_i2c(uint8_t addr_s);						//i2c recive data
		
void set_aknowledge(int state);
void Start_i2c(void);

void write_i2c(uint8_t character);
int read_i2c(void);	
	
void stop_i2c(void);

void ev5_i2c(void);
void ev6_i2c(void);

void ev8_i2c(void);
void ev8_1_i2c(void);
void ev8_2_i2c(void);

void ev7_i2c(void);
void ev7_1_i2c(void);
};
#endif