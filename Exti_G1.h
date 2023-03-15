#include "stm32f4xx.h"

#include "GP_M_1.h"

#ifndef Exti_G1_H
#define	Exti_G1_H
class Exti_G1:public GPIO_own_1
//class Exti_G1 
{
public:
	Exti_G1();
	~Exti_G1(){};
		
	void set_Exticr();		//set interrupt with assigned pin  //NVIC_EnableIRQ //IMR
	void set_Ftsr();			//falling edge
	void set_Rtsr();			//rising edge
	
		
		
};
#endif