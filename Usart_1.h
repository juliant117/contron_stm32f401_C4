#include "stm32f4xx.h"

#include "GP_M_1.h"

#ifndef Usart_1_H
#define	Usart_1_H

class Usart_1:public GPIO_own_1{
public:
	Usart_1();
	~Usart_1();

	USART_TypeDef * Usart_n;

void set_usart_n(int usart_n_in,int freq_usart);
//void set_usart_t_r(bool);

	

};
#endif