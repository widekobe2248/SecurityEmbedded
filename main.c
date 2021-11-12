//Main Files

//Base Include 
#include "stm32l053xx.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pir_sensor.h"
#include "keypad_sensor.h"
#include "queue.h"


//Function Init Prototypes
//Triggers
bool pir_trigger(void);
bool keypad_trigger(void);
bool alarm_trigger(queue_t *alarmQ, int16_t *data);
bool check_pass_trigger(void);
void wait(int time);
void init(void);
	
void init(void) {
	
	//Initalize CLock to Pains
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	
	
	//Pin Settings
	// Output=01  Input=00   Alternate Function=10   Analog IO = 11
	
	//PA 5 is on board LED set to Output
	GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
	GPIOA->MODER |= (01 << GPIO_MODER_MODE5_Pos);
	
	//PA 11 Is PIR Sensor Input Pin
	GPIOA->MODER &= ~GPIO_MODER_MODE11_Msk;
	GPIOA->MODER |= (0 << GPIO_MODER_MODE11_Pos);
	
	//Keypad Pins 
	//PB 13,14,15,1 are Output Pins For scanning Rows
	//Clear all Pins
	GPIOB->MODER &= ~GPIO_MODER_MODE13_Msk;
	GPIOB->MODER &= ~GPIO_MODER_MODE14_Msk;
	GPIOB->MODER &= ~GPIO_MODER_MODE15_Msk;
	GPIOB->MODER &= ~GPIO_MODER_MODE1_Msk;
	
	//Set All Pins
	GPIOB->MODER |= (01 << GPIO_MODER_MODE13_Pos);
	GPIOB->MODER |= (01 << GPIO_MODER_MODE14_Pos);
	GPIOB->MODER |= (01 << GPIO_MODER_MODE15_Pos);
	GPIOB->MODER |= (01 << GPIO_MODER_MODE1_Pos);
	
	
	//PB 2,11,12 are Input Pins for Reading Buttons
	//Clear all Pins
	GPIOB->MODER &= ~GPIO_MODER_MODE13_Msk;
	GPIOB->MODER &= ~GPIO_MODER_MODE13_Msk;
	GPIOB->MODER &= ~GPIO_MODER_MODE13_Msk;
	
	//Set All Pins
	GPIOB->MODER |= (00 << GPIO_MODER_MODE13_Pos);
	GPIOB->MODER |= (00 << GPIO_MODER_MODE13_Pos);
	GPIOB->MODER |= (00 << GPIO_MODER_MODE13_Pos);
	
	
	GPIOA->BSRR = (GPIO_BSRR_BS_5); //Turns on LED
	return;
}


//Voids for Main/Overhead
void wait(int time) {
	for(int i = 0; i < time; i++) { } 
}

//Checking If Password was Met Trigger
bool check_pass_trigger(void) {
	return true;
}

//Input Trigger
bool pir_trigger(void) { 
	return true; 
}

//Alarm Tripped Trigger
bool alarm_trigger(queue_t *alarmStatus, int16_t *data) { 
	if ( read_q(alarmStatus, data) ) {
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
	
	init();
	
	//Msg variables (Needed for reading to queues even if I do not care about the message)
	int16_t msg = 0;
	
	//Object Declaration
	queue_t alarmQ;
	queue_t alarmStatus;
	queue_t alarmReset;
	
	
	//Queue Initalizing
	init_queue(&alarmQ, 1);
	init_queue(&alarmStatus, 1);
	init_queue(&alarmReset, 1);


	//PIR Warm-Up (x Amount of Time)
	//8s
	wait(45000);
	

	while(1) {
		
		//Pir Sensor Task
		if( pir_trigger() ){
			static bool alarmOn = false;
			alarm_triggered(&alarmQ);
			
			//Checks if the queue was written to
			if( read_q(&alarmQ, &msg) || alarmOn ) {
				//Writes to the queue to turn alarm on and sets alarmOn to true
				alarmOn = true;
				write_q(&alarmStatus, 1);
			}
			else {
				alarmOn = false;
			}
			
		}
		

		//Keypad Sensor Task
		if( keypad_trigger() ) {
			//Gets Key Input and writes it to the AlarmReset Queue
			get_key_input(&alarmReset);
		}
			
		//Alarm Task
		if( alarm_trigger(&alarmStatus, &msg) ) {
			
			//If AlarmReset returns true then turn off the alarm
			if ( read_q(&alarmReset, &msg) ) {
				//Turn Off Alarm
			}
			else {
			//Turn On Alarm
			}
			
		}
		
		
		//break;
	}
}
