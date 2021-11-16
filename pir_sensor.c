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
//CRC This class is in charge of finding motion from the sensor and writing to a queue that
//is used in main
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
