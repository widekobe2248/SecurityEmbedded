//Kobe Johnson


#include "stm32l053xx.h"
#include <stdint.h>
#include <stdbool.h>
#include "queue.h"

//Writes the key to a queue for IPC
void get_key_input(queue_t *keyQ);
//Gets input for the get_key_input function (Helper function)
bool input_detected(void);
