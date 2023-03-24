#include "stm32f4xx.h"


#ifndef Control_PID_1_H
#define	Control_PID_1_H
class Control_PID_1{
	public:
		Control_PID_1();
		~Control_PID_1(){};
			
		double ref_signal=0;		//reference signal 
		double kp;						//const p
		double ki;						//const i
		double kd;						//const d
		
		double cur_error=0;			//current error
		double las_error=0;     //last error  error n-1
		double integral=0;			//calculate integral
		double derivate=0;			//calculate derivate
			
		double cur_sig=0;				//current signal
		double las_signal=0;		//last signal  signal n-1
		
		double out_signal=0;			//out signal;
			
		void set_ref_signal(double ref_in);      //set reference signal
		void set_conf(double kp_in,double ki_in,double kd_in);      //set kp,ki,kd
			
		double calculate_pid(double signal_in);			//calculate out signal
		
				
			
};	
#endif