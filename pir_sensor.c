//Kobe Johnson

#include "pir_sensor.h"

void init_pir(void)
{
	return;
}

bool motion_found(void) 
{
	//Reads sensor to determine if motion detected and returns the bool
	return false;
}

void alarm_triggered(queue_t *alarmQ)
{

	//Returns if motion was detected
	bool motion_detected = motion_found();
	
	if( motion_detected )
	{
		write_q(alarmQ, 1);
	}
	
	return;
}
