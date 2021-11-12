//Kobe Johnson

#include "pir_sensor.h"


//Reads sensor to determine if motion detected and returns the bool
bool motion_found(void) {
	uint32_t input = (GPIOA->IDR) & (1 << 11);
	if(input != 0){
		return true;
	}
	return false;
}

void alarm_triggered(queue_t *alarmQ) {
	

	//Returns if motion was detected
	bool motion_detected = motion_found();
	
	if( motion_detected )
	{
		write_q(alarmQ, 1);
	}
	
	return;
}
