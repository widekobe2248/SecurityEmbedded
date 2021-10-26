

#include "stm32l053xx.h"
#include <stdint.h>
#include "dac.h"

void start_noise()
{
}

void stop_noise()
{
}

void task_alarm()
{
	if(read_queue(&alarm_queue, &alarm_msg)==true)
	{
		start_noise();
	}
	else
	{
		stop_noise();
	}
}