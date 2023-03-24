#include "stm32f4xx.h"
#include "Control_PID_1.h"

#include <string.h>

Control_PID_1::Control_PID_1(){}
void Control_PID_1::set_ref_signal(double ref_in){	
//set reference signal
	ref_signal=ref_in;
	
} 
void Control_PID_1::set_conf(double kp_in,double ki_in,double kd_in){
	//set kp,ki,kd
	
	 kp=kp_in;						//const p
	 ki=ki_in;						//const i
	 kd=kd_in;						//const d
}
double Control_PID_1::calculate_pid(double signal_in){
		//calculate out signal
	cur_sig=signal_in;
	
	cur_error=ref_signal-cur_sig;
	integral +=cur_error;
	derivate =cur_error-las_error;
	las_error=cur_error;
		
	out_signal=kp*cur_error+ki*integral+kd*derivate;
	return(out_signal);	
}