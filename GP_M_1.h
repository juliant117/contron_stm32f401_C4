#include "stm32f4xx.h"

#ifndef GP_M_1_H
#define GP_M_1_H

class GPIO_own_1
{
	public:
	GPIO_own_1();
	~GPIO_own_1(){};
	
	int pin_GP;
	char bus_GP;
	
	GPIO_TypeDef * bus_pin;
	
	void b_set_pinbus(int pin,char bus);  //pin n (0,1,2...) bus n(A,b,C...)
	void b_MODER(int mod);								//set MODER on pin n
	void b_OTYPER(int oty);								//set OTYPER on pin n
	void b_OSPEEDR(int osped);						//set OSPEEDR on pin n
	void b_PUPDR(int pup);								//set PUPDR on pin n
	void b_FRLH(int ALTFUNC);							//set FRLH on pin n
	bool b_p_idr();												//return 1 in 
	void b_p_odr(bool out);               //1=on 0=off
		
};
#endif