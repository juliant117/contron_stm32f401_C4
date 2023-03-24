#include "GP_M_1.h" 
#include "stm32f4xx.h" 
#include <string>

using namespace std;

GPIO_own_1::GPIO_own_1(){}   //constructor

void GPIO_own_1::b_set_pinbus(int pin,char bus)   //constructor
{//pin n (0,1,2...) bus n(A,b,C...)
//concatenate bus GPIO
		pin_GP=pin;
		bus_GP=bus;

//enable clock   and set bus bus_pin
	switch (bus_GP)
	{
		case 'A':
		RCC->AHB1ENR |= 0X1<<0;
		this->bus_pin=GPIOA;
		break;
		case 'B':
		RCC->AHB1ENR |= 0X1<<1;
		this->bus_pin=GPIOB;
		break;
		case 'C':
		RCC->AHB1ENR |= 0X1<<2;
		this->bus_pin=GPIOC;
		break;
		case 'D':
		RCC->AHB1ENR |= 0X1<<3;
		this->bus_pin=GPIOD;
		break;
		case 'E':
		RCC->AHB1ENR |= 0X1<<4;
		this->bus_pin=GPIOE;
		break;
		case 'H':
		RCC->AHB1ENR |= 0X1<<7;
		this->bus_pin=GPIOH;
		break;
		default:
		this->bus_pin=GPIOB;	
	}
}

void GPIO_own_1::b_MODER(int mod)
{//set MODER on pin n
//MODER  00: Input (reset state)/	01: General purpose output mode/	10: Alternate function mode/	11: Analog mode
bus_pin -> MODER |= mod<<2*pin_GP;
}
void GPIO_own_1::b_OTYPER(int oty)
{//set OTYPER on pin n
//OTYPER	0: Output push-pull (reset state)/	1: Output open-drain
bus_pin -> OTYPER |= oty<<pin_GP;
}
void GPIO_own_1::b_OSPEEDR(int osped)
{//set OSPEEDR on pin n
//OSPEEDR	00: Low speed/ 01: Medium speed/ 10: High speed/ 11: Very high speed
bus_pin -> OSPEEDR |= osped<<2*pin_GP;
}
void GPIO_own_1::b_PUPDR(int pup)
{//set PUPDR on pin n
//PUPDR 	00: No pull-up, pull-down/ 01: Pull-up/ 10: Pull-down/ 11: Reserved/
bus_pin -> PUPDR |= pup<<2*pin_GP;	
}
void GPIO_own_1::b_FRLH(int ALTFUNC)
{//alternate functions just introduce alternate function
 //set FRLH  on pin n
	if((pin_GP>=0)&&(pin_GP<=7))
	{
		bus_pin-> AFR[0]|=ALTFUNC<<pin_GP*4;
	}
	else 
	{
		bus_pin-> AFR[1]|=ALTFUNC<<((pin_GP-8)*4);
	}
}

bool GPIO_own_1::b_p_idr(){
		
		pin_idr=((bus_pin->IDR & (0x1<<pin_GP))==(0x1<<pin_GP));
		//pin_idr=
		return pin_idr;
	
	}
		
void GPIO_own_1::b_p_odr(int out){//1=on 0=off 2=blink
	switch(out){
		case 0:			//off
		bus_pin ->ODR &=~ 0X1<<pin_GP;	
		break;
		case 1:			//on
		bus_pin ->ODR |= 0X1<<pin_GP;	
		break;
		case 2:			//blink
		bus_pin ->ODR ^= 0X1<<pin_GP;	
		break;
		default:
		bus_pin ->ODR ^= 0X1<<pin_GP;
	
	}
	
	
	}