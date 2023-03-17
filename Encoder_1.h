#include "stm32f4xx.h"

#ifndef Encoder_1_H
#define	Encoder_1_H
class Encoder_1:
{
	Encoder_1();
	~Encoder_1(){};
	
	int	n_pulses;   //count of pulses
	int	pwm_out;	//signal for both pwm   +/-
	int	freq_sample;  //freq of sample the angular speed
	bool way;   //turning sense   1/0
		
	
	void pwm_a();
	void pwm_b();	
	void exti_in_1();
	void in_2();
	void timmer_exti();
		
};	
#endif