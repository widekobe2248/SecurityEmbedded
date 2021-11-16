//Andrew Bartling
//Modified version of Sean Carrol's PWM code
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
//CRC Entry- This class is in charge of initalizing the timer for PWM
//And provides interface functions for the schedule in main for turning the timer on and off
#include "stm32l053xx.h"
#include <stdint.h>
#include "pwm_speaker.h"

void init_timer(void)
{
	RCC-> IOPENR |= RCC_IOPENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE0_Msk;
	GPIOA->MODER |= 2 << GPIO_MODER_MODE0_Pos; //Using PA0 as an output for PWM that will connect to the live wire of the speaker
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL0_Msk); // the ground wire of the speaker will be connected to ground
	GPIOA->AFR[0] |= 2 << GPIO_AFRL_AFSEL0_Pos;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->PSC = 100;  //Prescale divider
	TIM2->ARR = 8; // TOP
	TIM2->CCR1 = 4; // MATCH
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1
	| TIM_CCMR1_OC1PE; 
	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CR1 |= TIM_CR1_CMS_0; 
	TIM2->EGR |= TIM_EGR_UG; 
}



void enable_timer(void)
{
	TIM2->CR1 |= 1<< TIM_CR1_CEN_Pos;
	// This will allow us to enable the timer when the alarm is active
}

void disable_timer(void)
{
	TIM2->CR1 = 0;
	//This will allow us to disable the timer when the alarm is turned off
}
