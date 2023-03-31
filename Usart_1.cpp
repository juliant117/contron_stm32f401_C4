#include "stm32f4xx.h"
#include "Usart_1.h"

#include <string.h>

using namespace std;

Usart_1::Usart_1(){}
	
	
void Usart_1::set_usart_n(int usart_n_in,int freq_usart){
	switch(usart_n_in){
		case 1:
		RCC->APB2ENR |= 0X1<<4;     //enable clock usart1
		this->Usart_n=USART1;
		break;
		case 2:
		RCC->APB1ENR |= 0X1<<17;     //enable clock usart2
		this->Usart_n=USART1;
		break;
		case 6:
		RCC->APB2ENR |= 0X1<<5;     //enable clock usart6
		this->Usart_n=USART1;
		break;
	}
	
	Usart_n->CR1 |= 0X1<<13;	  // UE: USART enable
	Usart_n->CR1 |= 0X0<<12;		//M: Word length  0=8 1= 9  bits
	Usart_n->CR2 |= 0X0<<12;		// STOP: STOP bits    00=1 Stop bit  01=0.5 Stop bit    10=2 Stop bits   11=1.5 Stop bit
	
	//transmission
	Usart_n->CR3 |= 0X1<<7;			//DMAT: DMA enable transmitter
	Usart_n->CR1 |= 0X1<<3;			//TE: Transmitter enable
	
	//reception 
	Usart_n->CR3 |= 0X1<<6;			//DMAR: DMA enable receiver
	Usart_n->CR1 |= 0X1<<2;			// RE: Receiver enable
	
	
	//baud rate 
	int fck=16000000;
	int usart_div_in;
	usart_div_in=(fck)/(16*freq_usart);
	Usart_n->BRR=usart_div_in<<4;
	

	
	//((bus_pin->IDR & (0x1<<pin_GP))==(0x1<<pin_GP))
	
	
	/*
		if((Usart_n->SR) & (0x1 <<6)){
		Usart_n->DR = 'a';
	}
	*/
	
	
	/*
	if((Usart_n->SR) & (0x1 <<5)){
		data=Usart_n->DR; 
		Usart_n->SR&=~(0x5);
		
	}
	*/
}