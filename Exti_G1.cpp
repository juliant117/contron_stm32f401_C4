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
	int crx=(pin_GP%4);	//shift n to the right 
	int crxpx;          //SET BUS
	
	switch(bus_GP)
	{
		case 'A':
			crxpx=0x0;
		case 'B':
			crxpx=0x1;
		case 'C':
			crxpx=0x2;
		case 'D':
			crxpx=0x3;
		case 'E':
			crxpx=0x4;
		case 'H':
			crxpx=0x7;
		default:
			crxpx=0x0;
	}
	switch(crn)
	{//ITERRUPT
		case 0:
			NVIC_EnableIRQ(EXTI0_IRQn);
		case 1:
			NVIC_EnableIRQ(EXTI1_IRQn);
		case 2:
			NVIC_EnableIRQ(EXTI2_IRQn);
		case 3:
			NVIC_EnableIRQ(EXTI3_IRQn);
		default:
			NVIC_EnableIRQ(EXTI0_IRQn);
	}
	
	SYSCFG ->EXTICR[crn] |=crxpx<<pin_GP;
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
