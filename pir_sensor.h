//Kobe Johnson


#include "stm32l053xx.h"
#include <stdint.h>
#include <stdbool.h>
#include "queue.h"



//API
void init_pir(void);
void alarm_triggered(queue_t *alarmQ);


