#include "Exti_G1.h"
#include "stm32f4xx.h"

#include <string.h>

using namespace std;

Exti_G1::Exti_G1()
{
RCC->APB2ENR |= 0X1<<14;  // System configuration controller clock enable
}

void Exti_G1::set_Exticr()
{ 
	//set interrupt with assigned pin
	int crn=(pin_GP/4); //SET  NUMBER OF CR  1,2,3,4  
	int crx=(pin_GP%4);	//shift n to the left
	int crxpx;          //SET BUS
	int n_exti;
	

	if (pin_GP<5)
	{n_exti=pin_GP;
	}
	else if((5>=pin_GP) and (pin_GP<=9))
	{
		n_exti=5;
	}
	else//if((10>=pin_GP) and (pin_GP<=15))
	{
		n_exti=6;
	}
	
	switch(bus_GP)
	{
		case 'A':
			crxpx=0;
		break;
		case 'B':
			crxpx=1;
		break;
		case 'C':
			crxpx=2;
		break;
		case 'D':
			crxpx=3;
		break;
		case 'E':
			crxpx=4;
		break;
		case 'H':
			crxpx=7;
		break;
		default:
			crxpx=0;
	}
	
	switch(n_exti)
	{//ITERRUPT
		case 0:
		NVIC_EnableIRQ(EXTI0_IRQn);
		break;
		case 1:
		NVIC_EnableIRQ(EXTI1_IRQn);
		break;
		case 2:
		NVIC_EnableIRQ(EXTI2_IRQn);
		break;
		case 3:
		NVIC_EnableIRQ(EXTI3_IRQn);
		break;
	  case 4:
		NVIC_EnableIRQ(EXTI4_IRQn);
		break;
	  case 5:
		NVIC_EnableIRQ(EXTI9_5_IRQn);
		break;
		case 6:
		NVIC_EnableIRQ(EXTI15_10_IRQn);
		break;
		
		default:
		NVIC_EnableIRQ(EXTI0_IRQn);
	}
	
	SYSCFG ->EXTICR[crn] |=crxpx<<(crx*4);
	//SYSCFG ->EXTICR[3] |=0x2<<1*4;
	EXTI->IMR |= 0X1<<pin_GP;//IMR
}
void Exti_G1::set_Ftsr()
{ //falling edge
	 EXTI->FTSR |= 0X1<<pin_GP;
}
void Exti_G1::set_Rtsr()
{ //rising edge
	 EXTI->RTSR |= 0X1<<pin_GP;
}
