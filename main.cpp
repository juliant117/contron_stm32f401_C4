#include "stm32f4xx.h" 
#include <stdio.h>

#include "GP_M_1.h" 

#include "Timer_25.h"
#include "OutComp_25.h"
#include "Pwm_25.h"
#include "Exti_G1.h"

#include "Encoder_1.h"

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
// **********************  Wiii	**********************

int n_pulses=0;

extern "C"
{
void TIM3_IRQHandler(void){
	 TIM3->SR &=~1;
	GPIOA ->ODR ^= 0X1<<5;
	
}
void EXTI15_10_IRQHandler(void){
	EXTI->PR |= 0X1 << 13;
	n_pulses++;
	GPIOA ->ODR ^= 0X1<<5;
	
}
void EXTI0_IRQHandler(void){
	EXTI->PR |=0X1;
	if ((GPIOC -> IDR & 1<<1)==(0x1<<1))
		{
		n_pulses++;
		
		}
		else
		{
		n_pulses--;
	
		}
	//GPIOA ->ODR ^= 0X1<<5;
}

}

int main(void)
{

//pwm_pin();
//duty_probe();

	
pio_pin();
//timer_pin();	
	
	
//interrupt_c13();
	
//***************** Ecoder class
set_Encoder2();			//Encoder 2 settings 2_pwm 1_exti 1_idr 1_timmer

duty_probe();
while(1)
{
	//pc13 user button
	
}
}

void set_Encoder2(){
//settings encoder_2
enco_2.pwm_signal( 1, 0, 'A', 0x2,0x1, 2, 1, 0, 0,1);
enco_2.pwm_signal( 2, 1, 'A', 0x2,0x1, 2, 1, 0, 0,2);
enco_2.exti_in_1(  0, 'C',0);
enco_2.in_2( 1, 'C');
enco_2.timmer_exti( 3, 5, 1, 0);
	
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

