#include "stm32f4xx.h"

#include "Pwm_25.h"
#include "OutComp_25.cpp"
#include "Exti_G1.h"
#include "GP_M_1.h"


#ifndef Encoder_1_H
#define	Encoder_1_H

class Encoder_1:public Pwm_25,public Exti_G1,public GPIO_own_1,public OutComp_25
{
	public:
	Encoder_1();
	~Encoder_1(){};
	
	//two signals of pwm
	Pwm_25 pwm_s1;
	Pwm_25 pwm_s2;
	//one pin interrupt
	Exti_G1 exti_in;	
	//one idr
	GPIO_own_1  pin_in;
	//one timmer interrupt
	OutComp_25 out_tim;
	
		
	int	n_pulses;   	//count of pulses
	int	pwm_out;			//signal for both pwm   +/-
	int	freq_sample;  //freq of sample the angular speed
	bool way;   			//turning sense   1/0
		
	void pwm_a(Pwm_25 pwm_s1);	
	void pwm_b(Pwm_25 pwm_s2);	
	void exti_in_1(Exti_G1 exti_in);
	void in_2(GPIO_own_1  pin_in);
	void timmer_exti(OutComp_25 out_tim);
		
};	
#endif