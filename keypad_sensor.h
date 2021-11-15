//Kobe Johnson


#include "stm32l053xx.h"
#include <stdint.h>
#include <stdbool.h>
#include "queue.h"

//Writes the key to a queue for IPC
void get_key_input(queue_t *alarmReset);
//Gets the input number entered from keypad
int num_pressed(void);
//Returns True if the password has been entered
bool passwordEntered(int num_entered);

//wait helper funcntion
void waitFor(int amount);
