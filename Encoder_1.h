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
	
	//***************** own subclasses *****************
 	//two signals of pwm
	Pwm_25 pwm_s1;
	Pwm_25 pwm_s2;
	//one pin interrupt
	Exti_G1 exti_in;	
	//one idr
	GPIO_own_1  idr_in;
	//one timmer interrupt
	OutComp_25 out_tim;
	
	//***************** Encoder variable's *****************	
		
	int	n_pulses;   	//count of pulses
	int	pwm_out;			//signal for both pwm   +/-
	int	freq_sample;  //freq of sample the angular speed
	double speed;     //Encoder speed
		
//********************************** settings **********************************		
	
	void pwm_signal(int pmw_signal_n,int pin,char peripheric,int MODER_in,
									int Alter_f_in,int tim_n,int time_n,bool per_freq,bool arr_psc,
									int chan_in);							//pwm settings
									
	void exti_in_1( int pin_in,char peripheric,
								bool Rise_fall); 					//exti interrupt settings
	void in_2( int pin_n,	char peripheric);				//pin in settigs
	void timmer_exti(int tim_n,int time_n,
									bool per_freq,bool arr_psc);		//timmer interrupt settings
//********************************** logic **********************************
	void count_pulses();						//add and subtract the pulses
	
	void get_pulses();
	void set_pwm(int width_pwm);		//change both signals hust with the inpus signal + / - 
	void get_speed(int frecuency);
	
};	
#endif