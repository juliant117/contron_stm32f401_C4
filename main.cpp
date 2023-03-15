#include "stm32f4xx.h" 
#include <stdio.h>

#include "GP_M_1.h" 

#include "Timer_25.h"
#include "OutComp_25.h"
#include "Pwm_25.h"

#include "string.h"

using namespace std;

void pio_pin();
void timer_pin();
void pwm_pin();

Pwm_25 pwm_a0;
Pwm_25 pwm_a1;
int main(void)
{

pwm_pin();
//pio_pin();
pwm_a0.set_duty(50);	
pwm_a1.set_duty(5);
while(1)
{
}
}



//void pio_pin(){
//GPIO_own_1  led;
//led.b_set_pinbus(5,'A');	

//led.b_MODER(0x01);	
//GPIOA-> ODR |= 	0X1 <<5;
//}


//void timer_pin(){
////tim 2
//Tim_own_25 tim2;
//tim2.T_set_b(2);
//tim2.T_set_time(1,0,0);
//tim2.T_set_cr1(0);
//tim2.T_set_egr(0);
//}

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