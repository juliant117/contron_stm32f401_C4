#include "Pwm_25.h"
#include "stm32f4xx.h"

#include <string>

using namespace std;

Pwm_25 :: Pwm_25(){}

void Pwm_25 ::set_pwm()
{	//default pwm settings at default chanel on timmer
	Timmer_n->EGR|=0x1<<0;
	switch(channel)
	{
		case 1:
		Timmer_n -> CCMR1|=0x3<<5;  //Output compare 1 mode   PWM mode 1 -
		Timmer_n -> CCMR1|=0x1<<3;  //Output compare 1 preload enable
		Timmer_n -> CCER |=0x1<<0;	//signal is output on the corresponding output pin
		
		break;
		case 2:
		Timmer_n -> CCMR1|=0x3<<13;  
		Timmer_n -> CCMR1|=0x1<<11;
		Timmer_n -> CCER |=0x1<<4;
		break;
		case 3:
		Timmer_n -> CCMR2|=0x3<<5;  
		Timmer_n -> CCMR2|=0x1<<3;
		Timmer_n -> CCER |=0x1<<8;
		break;
		case 4:
		Timmer_n -> CCMR2|=0x3<<13;  
		Timmer_n -> CCMR2|=0x1<<11;
		Timmer_n -> CCER |=0x1<<12;
		break;
		
		default:
		Timmer_n -> CCMR1|=0x3<<5;  
		Timmer_n -> CCMR1|=0x1<<3;
	}
}
void Pwm_25 ::set_duty(int duty)
{ //duty %   -> arr=100%
	int duty_out;
	duty_out=(arr_o*duty)/100;
	switch(channel)
	{
		case 1:
		Timmer_n->CCR1 =duty_out;
		break;
		case 2:
		Timmer_n->CCR2 =duty_out;
		break;
		case 3:
		Timmer_n->CCR3 =duty_out;
		break;
		case 4:
		Timmer_n->CCR4 =duty_out;
		break;
		default:
		Timmer_n->CCR1 =duty_out;
	}
		
}