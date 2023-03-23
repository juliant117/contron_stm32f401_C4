#include "stm32f4xx.h"

#include <string.h>

#include "Encoder_1.h"

using namespace std;

//Encoder_1::Encoder_1(Pwm_25 a,Pwm_25 b,Exti_G1 c,GPIO_own_1 d,OutComp_25 e){
Encoder_1::Encoder_1(){}
	
void Encoder_1::pwm_signal(int pmw_signal_n,int pin,char peripheric,int MODER_in,
									int Alter_f_in,int tim_n,int time_n,bool per_freq,bool arr_psc,
									int chan_in){
	
	//select signal of pwm
	switch(pmw_signal_n){
		case 1:
			//pwm_s=pwm_s1;
		//GPIO
	pwm_s1.b_set_pinbus(pin,peripheric);  	//pin n (0,1,2...) bus n(A,b,C...)
	pwm_s1.b_MODER(MODER_in);				 	//moder(alern function 10 => 0x2)
	//Time
	pwm_s1.b_FRLH(Alter_f_in);						//altern function (0x0-0xf) on pin n 
	pwm_s1.T_set_b(tim_n);						//select timmer n (2-5)
	pwm_s1.T_set_time(time_n,per_freq,arr_psc);			//time / per_freq / arr_psc
	pwm_s1.T_select_channel(chan_in);		//select n channel 0-4
	pwm_s1.set_pwm();							//default pwm settings
	pwm_s1.T_set_cr1(0);					//cr1 0x1 enable
		break;
		case 2:
			//pwm_s=pwm_s2;
		//GPIO
	pwm_s2.b_set_pinbus(pin,peripheric);  	//pin n (0,1,2...) bus n(A,b,C...)
	pwm_s2.b_MODER(MODER_in);				 	//moder(alern function 10 => 0x2)
	//Time
	pwm_s2.b_FRLH(Alter_f_in);						//altern function (0x0-0xf) on pin n 
	pwm_s2.T_set_b(tim_n);						//select timmer n (2-5)
	pwm_s2.T_set_time(time_n,per_freq,arr_psc);			//time / per_freq / arr_psc
	pwm_s2.T_select_channel(chan_in);		//select n channel 0-4
	pwm_s2.set_pwm();							//default pwm settings
	pwm_s2.T_set_cr1(0);					//cr1 0x1 enable
		break;
	}									

}
									
				
									



void Encoder_1:: exti_in_1(int pin_in,char peripheric
														,bool Rise_fall){
	exti_in.b_set_pinbus(pin_in,peripheric);	//pin n (0,1,2...) bus n(A,b,C...)
	exti_in.set_Exticr();					//set interrupt with assigned pi
	if (Rise_fall!=0){
		exti_in.set_Rtsr();						//rising edge
	}
	else{
		exti_in.set_Ftsr();						//falling edge
	}
		
	
}	

void Encoder_1:: in_2(int pin_n,char peripheric){
	
	idr_in.b_set_pinbus(pin_n,peripheric);		//pin n (0,1,2...) bus n(A,b,C...)
}	

void Encoder_1:: timmer_exti(OutComp_25 out_tim,int tim_n,int time_n,
															bool per_freq,bool arr_psc){
	out_tim.T_set_b(tim_n);					//select timmer n (2-5)
	out_tim.T_set_time(time_n,per_freq,arr_psc);  //time / per_freq / arr_psc
	out_tim.T_set_cr1(0);				//cr1 0x1 enable
	out_tim.T_enab_int();				//enable interrupt
	out_tim.set_outcomp();			//set set_output compare at channel assigned
}		
