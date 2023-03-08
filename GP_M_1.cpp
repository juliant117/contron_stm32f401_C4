#include "GP_M_1.h" 
#include "stm32f4xx.h" 
#include <string>

using namespace std;
void set_bus(char bus);	
//ggpp 

GPIO_own_1::GPIO_own_1(int pin,char bus='B')   //constructor
{
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
{
//MODER  00: Input (reset state)/	01: General purpose output mode/	10: Alternate function mode/	11: Analog mode
bus_pin -> MODER |= mod<<2*pin_GP;
}
void GPIO_own_1::b_OTYPER(int oty)
{
//OTYPER	0: Output push-pull (reset state)/	1: Output open-drain
bus_pin -> OTYPER |= oty<<pin_GP;
}
void GPIO_own_1::b_OSPEEDR(int osped)
{
//OSPEEDR	00: Low speed/ 01: Medium speed/ 10: High speed/ 11: Very high speed
bus_pin -> OSPEEDR |= osped<<2*pin_GP;
}
void GPIO_own_1::b_PUPDR(int pup)
{
//PUPDR 	00: No pull-up, pull-down/ 01: Pull-up/ 10: Pull-down/ 11: Reserved/
bus_pin -> PUPDR |= pup<<2*pin_GP;	
}