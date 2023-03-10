#include "Timer_25.h"
#include "Pwm_25.h"
#include "stm32f4xx.h"

#include <string>

using namespace std;

Pwm_25 :: Pwm_25(){}
	
void Pwm_25 :: select_channel(int chan_in)
	
{
	//number of channel
	switch(chan_in)
	{
		case 1:
		Timmer_n -> CCMR1|=0x3<<5;  
		Timmer_n -> CCMR1|=0x1<<3;
		break;
		//default:
		
	}
}
