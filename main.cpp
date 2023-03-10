#include "stm32f4xx.h" 
#include <stdio.h>

#include "GP_M_1.h" 
#include "Timer_25.h"


//#include "string.h"

//using namespace std;

int main(void)
{

//GPIOA ->MODER |= 0x01<<2*5;   //A0 ALTER FUNCTION

//GPIO_own_1  led(5,'A');	
	
GPIO_own_1  led;
led.b_set_pinbus(5,'A');	

led.b_MODER(0x01);	
GPIOA-> ODR |= 	0X1 <<5;

//tim 2
Tim_own_25 tim2;
tim2.T_set_b(2);
tim2.T_set_time(1,0,0);
tim2.T_set_cr1(0);
tim2.T_set_egr(0);
	
	
	
while(1)
{
}
}

//led pin A 5