//Kobe Johnson
/*   Copyright 2021 Kobe Johnson & Andrew Bartling

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
//CRC Entry - This class is responsible for reading the input on the keypad through scanning
//It also writes to queues when a password is entered to reset the alarm
#include "keypad_sensor.h"

//Helper wait function needed to avoid warnings
void waitFor(uint16_t amount) {
	for(int i = 0; i < amount; i++) { } 
}

void get_key_input(queue_t *alarmReset) {
	static bool pressed = false;
	int16_t input_num = num_pressed();
	
	
	if(input_num == -1) {
		pressed = false;
	}
	else {
		//If password was entered send message to queue to turn off alarm
		//If it is still being pressed do not bother checking for continious input
		if( pressed != true ) {
			if( passwordEntered(input_num) ) {
				pressed = true;
				write_q(alarmReset, 1);					
			}
		}
	}
	
	
	return;
}



//Gets input for the get_key_input function (Helper function)
int16_t num_pressed(void) {
	
	//Check Row 1
	GPIOB->BSRR = (GPIO_BSRR_BS_13);
	waitFor(10);
	//Check Column 1
	uint32_t input = (GPIOB->IDR) & (1 << 2);
	if( input != 0 ) {
		return 1;
	}
	//Check Column 2
	input = (GPIOB->IDR) & (1 << 11);
	if( input != 0 ) {
		return 2;
	}
	//Check Column 3
	input = (GPIOB->IDR) & (1 << 12);
	if( input != 0 ) {
		return 3;
	}
	
	//Turn off Row One Output
	waitFor(10);
	GPIOB->BSRR = (GPIO_BSRR_BR_13);
	
	
	//Check Row 2
	GPIOB->BSRR = (GPIO_BSRR_BS_14);
	waitFor(10);
	//Check Column 1
	input = (GPIOB->IDR) & (1 << 2);
	if( input != 0 ) {
		return 4;
	}
	//Check Column 2
	input = (GPIOB->IDR) & (1 << 11);
	if( input != 0 ) {
		return 5;
	}
	//Check Column 3
	input = (GPIOB->IDR) & (1 << 12);
	if( input != 0 ) {
		return 6;
	}
	//Turn off Row Two Output
	waitFor(10);
	GPIOB->BSRR = (GPIO_BSRR_BR_14);
	
	
	//Check Row 3
	GPIOB->BSRR = (GPIO_BSRR_BS_15);
	waitFor(10);
	//Check Column 1
	input = (GPIOB->IDR) & (1 << 2);
	if( input != 0 ) {
		return 7;
	}
	//Check Column 2
	input = (GPIOB->IDR) & (1 << 11);
	if( input != 0 ) {
		return 8;
	}
	//Check Column 3
	input = (GPIOB->IDR) & (1 << 12);
	if( input != 0 ) {
		return 9;
	}
	//Turn off Row Three Output
	waitFor(10);
	GPIOB->BSRR = (GPIO_BSRR_BR_15);
	

	
	//Check Row 4
	GPIOB->BSRR = (GPIO_BSRR_BS_1);
	waitFor(10);
	//Check Column 2 because 1 and 3 does not have a number so ignore it
	input = (GPIOB->IDR) & (1 << 11);
	if( input != 0 ) {
		return 0;
	}
	//Turn off Row Four Output
	waitFor(10);
	GPIOB->BSRR = (GPIO_BSRR_BR_1);

	//If no input just return -1
	return -1;
}


//Checks if the password has been entered and handles recording inputs
bool passwordEntered(int16_t num_entered) {
	static uint16_t count = 0;
	
	
	//Working Code for entering fice 4 times to deactivate the alarm
	//Got it working Not enough time to make it more variable and work (But did try...a lot)
	if( num_entered == 9 ) {
		count = count + 1;
		if(count == 4)
		{
			count = 0;
			return true;
		}
	}
	else {
		return false;
	}
	
	
	//Just a last double check to ensure that if it does not do anything return false and ignore it
	return false;


}
