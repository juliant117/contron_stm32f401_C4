#include "stm32f4xx.h"
#ifndef Timer_25_H
#define	Timer_25_H

class Tim_own_25{
	public:
	
	Tim_own_25();
	~Tim_own_25();
	
	//char Timmer_n;
	int time;
	int arr_o;
	int psc_o;
	int cnt_o=0;
	TIM_TypeDef * Timmer_n;
	
	void T_set_b(int timmer);
	void T_set_time(int time_n,bool per_freq,bool arr_psc);
	void T_set_cnt(int cnt_in);
	void T_set_cr1(int cr1_in);
	void T_set_egr(int egr_in);
};

class Pwm_own:Tim_own_25{
	public:
		
};
#endif