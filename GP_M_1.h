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
	
	void b_set_pinbus(int pin,char bus);
	void b_MODER(int mod);
	void b_OTYPER(int oty);
	void b_OSPEEDR(int osped);
	void b_PUPDR(int pup);
	void b_FRLH(int ALTFUNC);
};
#endif