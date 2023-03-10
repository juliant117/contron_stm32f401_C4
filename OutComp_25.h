#include "stm32f4xx.h"

#include "GP_M_1.h"
#include "Timer_25.h"

#ifndef OutComp_25_H
#define	OutComp_25_H

class OutComp_25:public Tim_own_25 ,public GPIO_own_1{
	public:
		OutComp_25();
		~OutComp_25();
	TIM_TypeDef * Timmer_n_in;
	void select_channel(int chan_in);
	
};
#endif