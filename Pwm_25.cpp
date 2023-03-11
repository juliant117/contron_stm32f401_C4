#include "Pwm_25.h"
#include "stm32f4xx.h"

#include <string>

using namespace std;

Pwm_25 :: Pwm_25(){}
	
void Pwm_25 :: select_channel(int chan_in)
	
{
	Timmer_n->EGR|=0x1<<0;
	
	//number of channel
	switch(chan_in)
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
