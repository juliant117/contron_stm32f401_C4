#include "stm32f4xx.h" 
#include <stdio.h>

#include "GP_M_1.h" 

#include "Timer_25.h"
#include "OutComp_25.h"
#include "Pwm_25.h"
#include "Exti_G1.h"

#include "Encoder_1.h"
#include "Control_PID_1.h"

#include "string.h"

using namespace std;

void pio_pin();    //pin general purpose
void timer_pin(); //timer
void pwm_pin();   //pwm
void interrupt_c13();
	
void set_Encoder2();
void duty_probe();

// **********************  Encoder 1	**********************
GPIO_own_1  led;
// **********************  Encoder 2	**********************
Encoder_1 enco_2;
// **********************  control PID	1 **********************

Control_PID_1 cont_enc2;



// **********************  yo don't know **********************

int sys_tim[]={0,-20};    //contador para cambiar de velocidad (se puede con usart)

double pulse_n_n;
double error_control;
double out_control;
double reference_in_nose;

extern "C"
{
void SysTick_Handler(void){	
	sys_tim[0]++;
	if (sys_tim[0]>=100)
	{
	sys_tim[0]=0;
	sys_tim[1]++;	
		
	//******************** pid  ********************	
	//*****************  positionn ********************
	//enco_2.set_pwm(cont_enc2.calculate_pid(enco_2.n_pulses));
	//*****************  speed ********************
		enco_2.set_pwm(cont_enc2.calculate_pid(enco_2.speed));
		
	out_control=	cont_enc2.out_signal;
	error_control=cont_enc2.cur_error;
			
	
	if(sys_tim[1]>=100)
	{
		sys_tim[1]=-100;
	}
	
	}
	
}	
void TIM3_IRQHandler(void){
	TIM3->SR &=~1;
	GPIOA ->ODR ^= 0X1<<5;
	enco_2.get_speed(9);
	pulse_n_n=enco_2.speed;
}
void EXTI15_10_IRQHandler(void){
	EXTI->PR |= 0X1 << 13;
	GPIOA ->ODR ^= 0X1<<5;
	
}
void EXTI0_IRQHandler(void){
	EXTI->PR |=0X1;
	enco_2.count_pulses();
	//pulse_n_n=enco_2.n_pulses;
	
}

}

int main(void)
{
//***************** Systick **************************
	
	SystemCoreClockUpdate(); 
  SysTick_Config( SystemCoreClock/1000);
	
//***************** Ecoder class **************************	

//duty_probe();

pio_pin();

	
//***************** Ecoder class **************************
	set_Encoder2();			//Encoder 2 settings 2_pwm 1_exti 1_idr 1_timmer

  duty_probe();
	
	//******************** pid postion ********************
	reference_in_nose=15;
	cont_enc2.set_ref_signal(reference_in_nose);
	cont_enc2.set_conf(3,0.05,0.005);
	
	//******************** pid speed ********************
while(1)
{
	//pc13 user button
	
}
}
//****************** Settings Encoder_2 **************************
void set_Encoder2(){

enco_2.pwm_signal( 1, 0, 'A', 0x2,0x1, 2, 50, 1, 0,1);
enco_2.pwm_signal( 2, 1, 'A', 0x2,0x1, 2, 50, 1, 0,2);
enco_2.exti_in_1(  0, 'C',0);
enco_2.in_2( 1, 'C');
enco_2.timmer_exti( 3, 9, 1, 0);
	
}

void duty_probe(){
enco_2.pwm_s1.set_duty(0);	
enco_2.pwm_s2.set_duty(0);
}


void pio_pin(){
led.b_set_pinbus(5,'A');	
led.b_MODER(0x01);	
GPIOA-> ODR |= 	0X0 <<5;
}

