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
		
	SPI_TypeDef *i2c_n;	
		

};
#endif