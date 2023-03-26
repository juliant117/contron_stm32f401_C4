#include "stm32f4xx.h"

#include <string.h>

#include "Encoder_1.h"

using namespace std;

//Encoder_1::Encoder_1(Pwm_25 a,Pwm_25 b,Exti_G1 c,GPIO_own_1 d,OutComp_25 e){
Encoder_1::Encoder_1(){}
//********************************** settings **********************************
	void Encoder_1::set_number_pul_step(double n_pul_ste_rev_in){
		n_pul_ste_rev=n_pul_ste_rev_in;
	}
	
	void Encoder_1::pwm_signal(int pmw_signal_n,int pin,char peripheric,int MODER_in,
									int Alter_f_in,int tim_n,int time_n,bool per_freq,bool arr_psc,
									int chan_in){
										
	//select signal of pwm
	switch(pmw_signal_n){
		case 1:
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
									
void Encoder_1:: exti_in_1(int pin_in,char peripheric,bool Rise_fall){
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

void Encoder_1:: timmer_exti(int tim_n,int time_n,	bool per_freq,bool arr_psc){
	out_tim.T_set_b(tim_n);					//select timmer n (2-5)
	out_tim.T_set_time(time_n,per_freq,arr_psc);  //time / per_freq / arr_psc
	out_tim.T_set_cr1(0);				//cr1 0x1 enable
	out_tim.T_enab_int();				//enable interrupt
	out_tim.set_outcomp();			//set set_output compare at channel assigned
}		
void Encoder_1::sel_speed_pos(bool speed_pos_in){   //selec  speed=0 pos=1
	speed_pos=speed_pos_in;
}
//--------------- steeper ------------------------------

void Encoder_1::setp_d_4988(int sel_fun,int pin_n,	char peripheric){
	//settings of steps out pin bus
	//idr_in.b_set_pinbus(pin_n,peripheric);		//pin n (0,1,2...) bus n(A,b,C...)
	
	switch(sel_fun)
	{
		case 1:     //direction
		out_dir.b_set_pinbus(pin_n,peripheric);
		out_dir.b_MODER(0x1);
		break;
		case 2:			//step pulse
		out_n_s.b_set_pinbus(pin_n,peripheric);
		out_n_s.b_MODER(0x1);
		break;
	}
	
	
}
//********************************** logic ************************************
 void Encoder_1::count_pulses(){     //add and subtract the pulses
		if (idr_in.b_p_idr())
		{
		n_pulses++;
		
		}
		else
		{
		n_pulses--;
	
		}
}
	
void Encoder_1::get_pulses(){
		
}
void Encoder_1::set_pwm(int width_pwm){
	//change both signals hust with the inpus signal + / - 
	
	if (width_pwm>=1)						//positive signal
	{
		pwm_s1.set_duty(0);	
	  pwm_s2.set_duty(0);
		//for(int i=0;i<=10;i++)	{}		//time to wait to switch transistors
		pwm_s1.set_duty(width_pwm);	
	  pwm_s2.set_duty(0);
	}
	else if((width_pwm<1) and (width_pwm>-1))   //neutral signal
		{
		 pwm_s1.set_duty(0);	
	   pwm_s2.set_duty(0);
		}
	else if(width_pwm<-1)				//negative sigal
	{
		pwm_s1.set_duty(0);	
	  pwm_s2.set_duty(0);
		//for(int i=0;i<=10;i++)	{}		//time to wait to switch transistors
		pwm_s1.set_duty(0);	
	  pwm_s2.set_duty(-width_pwm);
	}
}

void Encoder_1::get_speed(int frecuency){  //calculate speed  rev/seg
	
  int n_time=10;      //   (rev/s)   n_time number of seconds
	speed=((n_pulses*frecuency*n_time)/n_pul_ste_rev);			
	n_pulses=0;
	
}
//--------------- steeper ------------------------------
void Encoder_1::send_steps(){
	//bool direction;7
	if(speed_pos==0){n_steps=1;}
		
	
	if (direction)
	{
		out_dir.b_p_odr(1);
	}
	else
	{
		out_dir.b_p_odr(0);
	}
	
	if(n_steps>=1)    //if this recive pulses >0  
	{
		out_n_s.b_p_odr(1);
		for(int i=0;i<100;i++)
    {
			__NOP();
		}
		out_n_s.b_p_odr(0);
		if(speed_pos){  //if we need speed n_steps is infinite
		n_steps--;
		}
		else{
		n_steps=1;
		}
	}
	
	//int n_steps;
	
}

void Encoder_1::set_steps(int steps_in){						//set number of steps
	//direction
	if (steps_in>=0)
	{ 
		direction=0;
		n_steps=steps_in;
	}
	else if (steps_in<0)
	{ 
		direction=1;
		n_steps=-steps_in;
	}
	
	
}

void Encoder_1::set_speed(double speed_in){				//set speed
																//1.8 degrees
		if (speed_in>=0)
		{ 
		direction=0;
		speed=speed_in;
		}
		else if (speed_in<0)
		{ 
		direction=1;
		speed=-speed_in;
		}
		//calculate frequency for reach the speed
	  int freq;
		freq=speed*200;  													//rev/seg
		out_tim.T_set_time(freq,1,1);
		
}
		