#include "stm32f4xx.h"

#include "GP_M_1.h"

#ifndef Usart_1_H
#define	Usart_1_H

class Usart_1:public GPIO_own_1{
public:
	Usart_1();
	~Usart_1();
		
	//***************** own subclasses *****************
	GPIO_own_1 own_tx;
	GPIO_own_1 own_rx;

	USART_TypeDef * Usart_n;

void set_usart_n(int usart_n_in,int freq_usart); //usart_settings
void set_usart_tx(int pin, char bus,int afr);
void set_usart_rx(int pin, char bus,int afr);


void send_usart(char data);			//usart send data

char recive_data();			//usart recive data
	

};
#endif