//Main Files

//Base Include 
#include "stm32l053xx.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pir_sensor.h"
#include "queue.h"


//Function Init Prototypes
//Triggers
bool pir_trigger(void);
bool keypad_trigger(void);
bool alarm_trigger(void);


//Voids for Main/Overhead
void wait(int time)
{
	for(int i = 0; i < time; i++) { return; }
}



//Input Trigger
bool pir_trigger(void) { 
	return true; 
}

//Alarm Tripped Trigger
bool alarm_trigger(void) { 
	return true;
}

//Keypad Trigger
bool keypad_trigger(void) {
	return true; 
}

int main(void)
{
	
	//Object Declaration
	queue_t alarmQ;
	queue_t alarmStatus;
	
	
	//Array Declaration
	int pinCorrect[4] = {1, 3, 5, 8};
	int pinMemory[4];
	
	
	//PIR Warm-Up (x Amount of Time)
	//Not sure on time yet
	wait(1);
	
	//Schedule Loop For Tasks
	while(1)
	{
		if( pir_trigger() ){
			//This needs some way to have a state
			//Not a full fsm
			//But needs to know if it has already been triggered to write to the queue again
			//Needed to keep alarm on even if the PIR does not detect to keep alarm moving
			int16_t msg = 0;
			alarm_triggered(&alarmQ);
			if( read_q(&alarmQ, &msg) )
			{
				//Writes to the queue to turn alarm on
				write_q(&alarmStatus, 1);
			}
			
			//Gets Inputs for PIR
		}
		
		
		
		if( keypad_trigger() ) {
			//Gets input for Keypad
		}
			
		if( alarm_trigger() ) {
			
			//Runs the alarm to Run
		}
		
		
		break;
	}
}
