#include "stm32f4xx.h" 
#include <stdio.h>

#include "GP_M_1.h" 

//#include "string.h"

//using namespace std;

int main(void)
{

//GPIOA ->MODER |= 0x01<<2*5;   //A0 ALTER FUNCTION
GPIO_own_1  led(5,'A');
led.b_MODER(0x01);	
GPIOA-> ODR |= 	0X1 <<5;
	
while(1)
{
}
}

//led pin A 5