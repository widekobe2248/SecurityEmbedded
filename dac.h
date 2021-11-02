//Written by Andrew Bartling
//Digital to Analog Converter


#include "stm32l053xx.h"
#include <stdint.h>

void init_dac();
void start_noise();
void end_noise();

extern alarm_queue;
int16_t alarm_msg;
