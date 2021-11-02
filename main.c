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
bool alarm_trigger(queue_t *alarmQ, int16_t *data);
void wait(int time);
void init(void);
	
void init(void) {
	
	return;
}


//Voids for Main/Overhead
void wait(int time) {
	for(int i = 0; i < time; i++) { } 
}



//Input Trigger
bool pir_trigger(void) { 
	return true; 
}

//Alarm Tripped Trigger
bool alarm_trigger(queue_t *alarmQ, int16_t *data) { 
	if ( read_q(alarmQ, data) ) {
		return true;
	}
	else {
		return false;
	}
}

//Keypad Trigger
bool keypad_trigger(void) {
	return true; 
}


int main(void) {
	//Msg variables
	int16_t msg = 0;
	
	//Object Declaration
	queue_t alarmQ;
	queue_t alarmStatus;
	queue_t alarmReset;
	
	
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
			alarm_triggered(&alarmQ);
			
			//Checks if the queue was written to
			if( read_q(&alarmQ, &msg) ) {
				//Writes to the queue to turn alarm on
				write_q(&alarmStatus, 1);
			}
			
		}
		
		
		
		if( keypad_trigger() ) {
			//Gets input for Keypad
		}
			
		if( alarm_trigger(&alarmStatus, &msg) ) {
			
			//Runs the alarm to Run
		}
		
		
		break;
	}
}
