#include "stm32f4xx.h"
#include "I2c_own_1.h"

#include <string.h>
using namespace std;

I2c_own_1::I2c_own_1(){}
	
	
void I2c_own_1::set_i2c_n(int i2c_n_in,int freq_i2c,int clokfreq){//number of i2c  /  freq i2c  M Hz/ fre1 clock apb   KHz
 	//enable rcc and select number of i2c
	switch(i2c_n_in)
	{
		case 1:
		RCC->APB2ENR |= 0X1<<21;     //enable clock i2c 1
		this->i2c_n=I2C1;
		
		break;
		case 2:
		RCC->APB2ENR |= 0X1<<22;     //enable clock i2c	2
		this->i2c_n=I2C2;
		
		break;
		case 3:
		RCC->APB2ENR |= 0X1<<23;     //enable clock i2c	3
		this->i2c_n=I2C3;
		
		break;
	
		
	//RCC peripherics  time-i2c	
	i2c_n->CR1 |= (0x1<<15);   	// Software reset
	i2c_n->CR1 &=~ (0x1<<15);   	// Software reset
	
	//********************************          ********************************
	//default clock stm 16 MHz
	//select time, this works just for standar mode with max 100 KHz 
	//standard mode
	
	float tr_slc=1000,tw_sclh=4000,Tclock=0,Ti2c=0;
	int T_ccr=0,t_trise=0;
	//clock apb frequency on MHz
	i2c_n-> CR2 |= clokfreq;   				//set frequency M Hz FREQ[5:0]: Peripheral clock frequency
	Tclock=(1000/clokfreq);
	Ti2c=((1*10^6)/freq_i2c);				//time of clock in ns 
		
	//T_ccr=((tr_slc+tw_sclh)/(Tclock));		//solamente genera la maxima frecuencia
	T_ccr=	(Tclock/(2*Ti2c));
	i2c_n->CCR |= T_ccr;								//CCR[11:0]  Clock control register in Fm/Sm mode (Master mode)  T ns   dec40-> 100KHz    dec10 -> 400kHz
	//t_trise=(tr_slc/Tclock)+1;
	
	i2c_n->TRISE|= clokfreq+1;						// TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)	
	
	//********************************          ********************************
	i2c_n->CR1 |= (0x1<<0);   	//enable i2c 
	}
}

void I2c_own_1::set_i2c_scl(int pin, char bus,int afr){
	
	own_scl.b_set_pinbus(pin,bus);
	own_scl.b_MODER(0x2);
	own_scl.b_FRLH(afr);
	own_scl.b_OTYPER(0x1);
	own_scl.b_OSPEEDR(0x3);
	own_scl.b_PUPDR(0x1);
}

void I2c_own_1::set_i2c_sda(int pin, char bus,int afr){

	own_sda.b_set_pinbus(pin,bus);
	own_sda.b_MODER(0x2);
	own_sda.b_FRLH(afr);
	own_sda.b_OTYPER(0x1);
	own_sda.b_OSPEEDR(0x3);
	own_sda.b_PUPDR(0x1);
	
	
}	


//***************** i2c event stream *****************
void I2c_own_1::addres_transmit_i2c(uint8_t addr_s){
		I2C1->DR = addr_s<<1;			// write addres

}
void I2c_own_1::addres_recive_i2c(uint8_t addr_s){
	addr_s=addr_s<<1;
	addr_s |= 0x1;
	I2C1->DR = addr_s;			// write addres
}


void I2c_own_1::write_i2c(uint8_t character){
	I2C1->DR = character;// write data	
}
int I2c_own_1::read_i2c(void){
	int8_t data;
	data= I2C1->DR;
	return data;
}	

void I2c_own_1::Start_i2c_3(void){
I2C1->CR1 |= (0x1<<8);			// START: Start generation
}


	
void I2c_own_1::stop_i2c(void){
	I2C1->CR1 |= (0x1<<9);			//  STOP: Stop generation
}

void I2c_own_1::ev5_i2c(void){
	//EV5: SB =1, cleared by reading SR1 register followed by writing DR register with addres
	while(!((I2C1->SR1) & (0x1<<0)));      //Start bit (Master mode)

}
void I2c_own_1::ev6_i2c(void){
//EV6: ADDR=1,cleared by reading SR1 register followed by reading SR2
	while(!((I2C1->SR1) & (0x1<<1)));      // ADDR: Address sent (master mode)/matched (slave mode)
	
	uint8_t temp = I2C1->SR1;   // read SR1 and SR2 to clear the ADDR bit
	temp = I2C1->SR2;
}

void I2c_own_1::ev8_i2c(void){
	//TxE=1, shift register not empty, data register empty, cleared by writing DR register
	while(!((I2C1->SR1) & (0x1<<7)));   //TxE: Data register empty (transmitters) 

	//while(!((I2C1->SR1) & (0x1<<7)));   //TxE: Data register empty (transmitters) 

}
void I2c_own_1::ev8_1_i2c(void){
//TxE=1, shift register empty,. data register empty, write Data1 in DR.
	while(!((I2C1->SR1) & (0x1<<7)));   //TxE: Data register empty (transmitters) 

}
void I2c_own_1::ev8_2_i2c(void){
//TxE=1, BTF=1, program stop request. Txe and BTF are cleared by hardware by the stop condition
	//while(!((I2C1->SR1) & (0x1<<7)));   //TxE: Data register empty (transmitters) 
	while(!((I2C1->SR1) & (0x1<<2)));		// BTF: Byte transfer finished
	
}

void I2c_own_1::ev7_i2c(void){
	//RxNE=1 cleared by reading DR register.
	while(!((I2C1->SR1) & (0x1<<6)));		// RxNE: Data register not empty (receivers)

}
void I2c_own_1::ev7_1_i2c(void){
	//RxNE=1 cleared by reading DR register, program ACK=0 and stop request.
	while(!((I2C1->SR1) & (0x1<<6)));		// RxNE: Data register not empty (receivers)
	I2C1->CR1 &=~ (0x1<<10);			// ACK: Acknowledge enable

}