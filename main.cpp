#include "stm32f4xx.h" 
#include <stdio.h>

#include "GP_M_1.h" 

//#include "Timer_25.h"
//#include "OutComp_25.h"
//#include "Pwm_25.h"

#include "string.h"

using namespace std;

void pio_pin();
void timer_pin();
void pwm_pin();

int main(void)
{

//pwm_pin();
pio_pin();
	
while(1)
{
}
}



void pio_pin(){
GPIO_own_1  led;
led.b_set_pinbus(0,'A');	

led.b_MODER(0x01);	
GPIOA-> ODR |= 	0X1 <<5;
}


//void timer_pin(){
////tim 2
//Tim_own_25 tim2;
//tim2.T_set_b(2);
//tim2.T_set_time(1,0,0);
//tim2.T_set_cr1(0);
//tim2.T_set_egr(0);
//}

//void pwm_pin(){
////pwm tim2 A0
////GPIO
//Pwm_25 pwm_a25;
//pwm_a25.b_set_pinbus(0,'A');
//pwm_a25.b_MODER(0x2);
//pwm_a25.b_FRLH(0x1);
////Time
//pwm_a25.T_set_b(2);
//pwm_a25.T_set_time(1,0,0);

//pwm_a25.T_select_channel(1);
//pwm_a25.set_pwm();
//pwm_a25.set_duty(5);	
//}