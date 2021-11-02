

#include "stm32l053xx.h"
#include <stdint.h>
#include "dac.h"

void init_dac()
{
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk); 
	GPIOA->MODER |= 3<<GPIO_MODER_MODE4_Pos; 
	
	
	RCC->APB1ENR |= 1<<RCC_APB1ENR_DACEN_Pos;
	RCC->APB2ENR |= 1<<RCC_APB2ENR_TIM21EN_Pos;
	
	
	DAC->CR |= 1<<DAC_CR_TEN1_Pos;
	
	DAC->CR |= 3<<DAC_CR_TSEL1_Pos;
	DAC->CR |= 1<<DAC_CR_WAVE1_Pos;
	DAC->CR |= 8<<DAC_CR_MAMP1_Pos;
	DAC->DHR12R1 |= 511<<DAC_DHR12R1_DACC1DHR_Pos;
	
	DAC->CR |= 0<<DAC_CR_BOFF1_Pos;
	
	DAC->CR |= 1<<DAC_CR_EN1_Pos;
	
	TIM21->CR1|= 1<<TIM_CR1_CKD_Pos;
	TIM21->CR1|= 0<<TIM_CR1_CMS_Pos;
	TIM21->CR1|= 0<<TIM_CR1_DIR_Pos;
	TIM21->CR1|= 1<<TIM_CR1_CEN_Pos;
	TIM21->CR2 |= 2<<TIM_CR2_MMS_Pos;
	TIM21->PSC |= 49<<TIM_PSC_PSC_Pos;
	TIM21->CNT |= 100<<TIM_CNT_CNT_Pos;
}

void start_noise()
{
	
}

void stop_noise()
{
	
}

void task_alarm()
{
	if(read_queue(&alarm_queue, &alarm_msg)==true)
	{
		start_noise();
	}
	else
	{
		stop_noise();
	}
}