//Andrew Bartling
//Modified version of Sean Carrol's PWM code

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
	TIM2->CR1 |= 1<<TIM_CR1_CEN_Pos;
	// This will allow us to enable the timer when the alarm is active
}

void disable_timer(void)
{
	TIM2->CR1 = 0;
	//This will allow us to disable the timer when the alarm is turned off
}
