#include "stm32f4xx.h"
#include "OutComp_25.h"

#include <string>

OutComp_25 :: OutComp_25(){}
	
void OutComp_25 :: set_outcomp()
{
	
		switch (channel)
	{///Interrupt enable register
		case 1:		//: Capture/Compare 1 interrupt enable
		Timmer_n->	DIER|=0x1<<1;
		break;
		case 2:
		Timmer_n->	DIER|=0x1<<2;
		break;
		case 3:
		Timmer_n->	DIER|=0x1<<3;
		break;
		case 4:
		Timmer_n->	DIER|=0x1<<4;
		break;
		default:
		Timmer_n->	DIER|=0x1<<0;
	
	}
}