#include "stm32f4xx.h"

#include "Pwm_25.h"
#include "OutComp_25.h"
#include "Exti_G1.h"
//#include "GP_M_1.h"


#ifndef Encoder_1_H
#define	Encoder_1_H

class Encoder_1:public Pwm_25,public Exti_G1,public OutComp_25 //,public GPIO_own_1
{
	public:
	//Encoder_1(Pwm_25,Pwm_25,Exti_G1,GPIO_own_1,OutComp_25);
	Encoder_1();
	~Encoder_1(){};
	
	//two signals of pwm
	Pwm_25 pwm_s1;
	Pwm_25 pwm_s2;
		
	//one pin interrupt
	Exti_G1 exti_in;	
	//one idr
	GPIO_own_1  idr_in;
	//one timmer interrupt
	OutComp_25 out_tim;
	
		
	int	n_pulses;   	//count of pulses
	int	pwm_out;			//signal for both pwm   +/-
	int	freq_sample;  //freq of sample the angular speed
	bool way;   			//turning sense   1/0
	
	void set_objects(Pwm_25 pwm_in1,Pwm_25 pwm_in2,Exti_G1 exti_in,GPIO_own_1  pin_in,OutComp_25 out_tim);
		
	void pwm_signal(int pmw_signal_n,int pin,char peripheric,int MODER_in,
									int Alter_f_in,int tim_n,int time_n,bool per_freq,bool arr_psc,
									int chan_in);							//pwm settings
									
	void exti_in_1( int pin_in,char peripheric,
								bool Rise_fall); 					//exti interrupt settings
	void in_2( int pin_n,	char peripheric);				//pin in settigs
	void timmer_exti(OutComp_25 out_tim,int tim_n,int time_n,
									bool per_freq,bool arr_psc);		//timmer interrupt settings
		
};	
#endif