#include "stm32f4xx.h"

#include "Timer_25.h"
#include <string.h>

using namespace std;

Tim_own_25::Tim_own_25(){}
	
void Tim_own_25::T_set_b(int n_timmer)
{	//bus timmer (2,3,4,5) ....
	//select timmer 2-5
	bus_n=n_timmer;
	switch(n_timmer)
	{
		case 2:
		RCC->APB1ENR |= 0X1<<0;     //enable clock tim2
		this->Timmer_n=TIM2;
		break;
		case 3:
		RCC->APB1ENR |= 0X1<<1;			//enable clock tim3
		this->Timmer_n=TIM3;
		break;
		case 4:
		RCC->APB1ENR |= 0X1<<2;			//enable clock tim4
		this->Timmer_n=TIM4;
		break;
		case 5:
		RCC->APB1ENR |= 0X1<<3;			//enable clock tim5
		this->Timmer_n=TIM5;
		break;
		default:
		this->Timmer_n=TIM2;
	}
}
void Tim_own_25::T_set_time(int time_n,bool per_freq,bool arr_psc)  
{//time   period s    frecuecy Hz
//per_freq    0 period    frequency
//arr_psc			    0=calculate psc    1=calculate arr 

	int F_clock=8000000;   //frecuencia de reloj por defecto
		time =time_n;
  if(arr_psc)
	{	//arr default   //caculate psc
		if (per_freq!=1)
		{ //period
			arr_o=1999;  //1999 by default
			psc_o=((2*F_clock*(time))/(arr_o-1))-1;
		}
		else
		{ //frecueny
			arr_o=1999;  //1999 by default
			psc_o=((2*F_clock)/((arr_o-1)*(time)))-1;
		}
	}
	else
	{	//psc default	//caculate arr
		if (per_freq!=1)
		{ //period
			psc_o=1999;  //1999 by default
			arr_o=((2*F_clock*(time))/(psc_o-1))-1;
		}
		else
		{ //frecueny
			psc_o=1999;  //1999 by default
			arr_o=((2*F_clock)/((psc_o-1)*(time)))-1;
		}
	}
	Timmer_n->ARR=arr_o;
	Timmer_n->PSC=psc_o;
}

void  Tim_own_25::T_set_cnt(int cnt_in)
{//set_cnt
//
Timmer_n->CNT=cnt_in;   
}
void Tim_own_25::T_set_cr1(int cr1_in)
{//set_cr1
//0 Counter enable
//1 Update disable
//
	Timmer_n->CR1=0x1<<cr1_in;
}

void Tim_own_25::T_enab_int()
{//enable interrupt
	int timer_n =bus_n;
	Timmer_n-> DIER|=0x1;
switch(timer_n)
	{
		case 2:
		NVIC_EnableIRQ(TIM2_IRQn);  //enable timmer interrupt
		break;
		case 3:
		NVIC_EnableIRQ(TIM3_IRQn);
		break;
		case 4:
		NVIC_EnableIRQ(TIM4_IRQn);
		break;
		case 5:
		NVIC_EnableIRQ(TIM5_IRQn);
		break;
		default:
		NVIC_EnableIRQ(TIM2_IRQn);
	}
}

void Tim_own_25::T_select_channel(int chan_in)
{	//number of channel 
	this->channel=chan_in;
}
