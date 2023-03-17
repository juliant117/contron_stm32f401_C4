#include "stm32f4xx.h" 
#include <stdio.h>

#include "GP_M_1.h" 

#include "Timer_25.h"
#include "OutComp_25.h"
#include "Pwm_25.h"
#include "Exti_G1.h"

#include "string.h"

using namespace std;

void pio_pin();    //pin general purpose
void timer_pin(); //timer
void pwm_pin();   //pwm
void interrupt_c13();
	

Pwm_25 pwm_a0;
Pwm_25 pwm_a1;
OutComp_25 a5;
Exti_G1 pc13;
GPIO_own_1  led;

int n_pulses=0;

extern "C"
{
void TIM3_IRQHandler(void){
	 TIM3->SR &=~1;
	//GPIOA ->ODR ^= 0X1<<5;
	
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
	GPIOA ->ODR ^= 0X1<<5;
}

}

int main(void)
{

//pwm_pin();
pio_pin();
timer_pin();
//pwm_a0.set_duty(0);	
//pwm_a1.set_duty(0);
	
//interrupt_c13();
while(1)
{
	//pc13 user button
	
}
}



void pio_pin(){

led.b_set_pinbus(5,'A');	

led.b_MODER(0x01);	
GPIOA-> ODR |= 	0X0 <<5;
	
	
pc13.b_set_pinbus(13,'C');
pc13.set_Exticr();
pc13.set_Ftsr();
//NVIC_EnableIRQ(EXTI15_10_IRQn);
}


void interrupt_c13()
{
	/*interrupcion por flancos en encoder*/
	RCC->AHB1ENR |= 0X1<<2;  //clock gpio c
	//GPIOC ->MODER |= 0x1<<1;   //C0 ALTER FUNCTION
	//GPIOC -> AFR[0] |= 0x1;    //C0 alterfunction af01 
	
	
	//RCC->APB2ENR |= 0X1<<14;
	
	SYSCFG ->EXTICR[0] |=0X2;
	EXTI->IMR |= 0X1;
	EXTI->FTSR |= 0X1;
	//NVIC_EnableIRQ(EXTI0_IRQn);
}


void timer_pin(){
//tim 3
//Tim_own_25 tim3;
//tim3.T_set_b(3);
//tim3.T_set_time(5,1,0);
//tim3.T_set_cr1(0);
//tim3.T_enab_int();
	

a5.T_set_b(3);
a5.T_set_time(2,1,0);  //
a5.T_set_cr1(0);
a5.T_enab_int();
a5.set_outcomp();


}

void pwm_pin(){
//pwm tim2 A0
//GPIO
 
pwm_a0.b_set_pinbus(0,'A');		
pwm_a0.b_MODER(0x2);					
pwm_a0.b_FRLH(0x1);						
//Time
pwm_a0.T_set_b(2);						//set timer
pwm_a0.T_set_time(1,0,0);			//setting time

pwm_a0.T_select_channel(1);		//select channel
pwm_a0.set_pwm();							//pwm

pwm_a0.T_set_cr1(0); 					//enable cr1 
//	
//pwm tim2 A1
//GPIO
pwm_a1.b_set_pinbus(1,'A');		//pin 1 bus a
pwm_a1.b_MODER(0x2);					
pwm_a1.b_FRLH(0x1);		
	
pwm_a1.T_set_b(2);						//set timer
pwm_a1.T_set_time(1,0,0);			//setting time

pwm_a1.T_select_channel(2);		//select channel
pwm_a1.set_pwm();							//pwm
pwm_a1.T_set_cr1(0); 					//enable cr1 

}