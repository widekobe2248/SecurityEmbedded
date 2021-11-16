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

#include "stm32l053xx.h"
#include <stdint.h>
#include <stdbool.h>
#include "queue.h"

//Writes the key to a queue for IPC
void get_key_input(queue_t *alarmReset);
//Gets the input number entered from keypad
int16_t num_pressed(void);
//Returns True if the password has been entered
bool passwordEntered(int16_t num_entered);

//wait helper funcntion
void waitFor(uint16_t amount);
