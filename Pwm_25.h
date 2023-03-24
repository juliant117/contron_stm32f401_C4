#include "stm32f4xx.h"

#include "GP_M_1.h"
#include "Timer_25.h"

#ifndef Pwm_25_H
#define Pwm_25_H

class Pwm_25:public Tim_own_25 ,public GPIO_own_1
//class Pwm_25
{
	public:
		Pwm_25();
	 ~Pwm_25(){};
	
	void set_pwm(); 						//default pwm settings at default chanel on timmer
	void set_duty(int duty);		//set duty    0%-100%
};
#endif