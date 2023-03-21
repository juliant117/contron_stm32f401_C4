#include "stm32f4xx.h"

#include <string.h>

#include "Encoder_1.h"

using namespace std;

Encoder_1::Encoder_1(){}
	
void Encoder_1::pwm_a(Pwm_25 pwm_s1){
	
	//GPIO
	pwm_s1.b_set_pinbus(0,'A');  	//pin n (0,1,2...) bus n(A,b,C...)
	pwm_s1.b_MODER(0x2);				 	//moder(alern function 10 => 0x2)
	//Time
	pwm_s1.b_FRLH(0x1);						//altern function (0x0-0xf) on pin n 
	pwm_s1.T_set_b(2);						//select timmer n (2-5)
	pwm_s1.T_set_time(1,0,0);			//time / per_freq / arr_psc
	pwm_s1.T_select_channel(1);		//select n channel 0-4
	pwm_s1.set_pwm();							//default pwm settings
	pwm_s1.T_set_cr1(0);					//cr1 0x1 enable
}
void Encoder_1:: pwm_b(Pwm_25 pwm_s2){
	//GPIO
	pwm_s2.b_set_pinbus(1,'A');		//pin n (0,1,2...) bus n(A,b,C...)
	pwm_s2.b_MODER(0x2);					//moder(alern function 10 => 0x2)
	//Time
	pwm_s2.b_FRLH(0x1);						//altern function on pin n
	pwm_s2.T_set_b(2);						//select timmer n (2-5)
	pwm_s2.T_set_time(1,0,0);			//time / per_freq / arr_psc
	pwm_s2.T_select_channel(1);		//select n channel 0-4
	pwm_s2.set_pwm();							//default pwm settings
	pwm_s2.T_set_cr1(0);					//cr1 0x1 enable
}	
void Encoder_1:: exti_in_1(Exti_G1 exti_in){
	exti_in.b_set_pinbus(13,'C');	//pin n (0,1,2...) bus n(A,b,C...)
	exti_in.set_Exticr();					//set interrupt with assigned pi
	exti_in.set_Ftsr();						//falling edge
}	

void Encoder_1:: in_2(GPIO_own_1  pin_in){
	pin_in.b_set_pinbus(5,'A');		//pin n (0,1,2...) bus n(A,b,C...)
}	

void Encoder_1:: timmer_exti(OutComp_25 out_tim){
	out_tim.T_set_b(3);					//pin n (0,1,2...) bus n(A,b,C...)
	out_tim.T_set_time(2,1,0);  //time / per_freq / arr_psc
	out_tim.T_set_cr1(0);				//cr1 0x1 enable
	out_tim.T_enab_int();				//enable interrupt
	out_tim.set_outcomp();			//set set_output compare at channel assigned
}		
