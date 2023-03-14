#include "stm32f4xx.h"

#ifndef Timer_25_H
#define	Timer_25_H

class Tim_own_25
{
	public:
	
	Tim_own_25();
	~Tim_own_25(){};
	
	//char Timmer_n;
	int time;
	int arr_o;
	int psc_o;
	int cnt_o=0;
	int bus_n;
	int channel;
	
	TIM_TypeDef * Timmer_n;
	
	void T_set_b(int timmer);      //bus timmer tim2 ....
	void T_set_time(int time_n,bool per_freq,bool arr_psc); //time or frequency
	void T_set_cnt(int cnt_in);			//cnt 
	void T_set_cr1(int cr1_in);			//cr1 
	void T_set_egr(int egr_in);			//egr
	void T_enab_int();							//enable interrupt
	void T_select_channel(int chan_in);		//select channel

};
#endif