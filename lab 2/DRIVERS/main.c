#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void delay();

int main(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  while (1) {
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15) != 0) {
			GPIO_SetBits(GPIOA, GPIO_Pin_4);
			delay(300);
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
			delay(300);
		} else {
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		}
  }
}

void delay(void)
{
	for(int i = 0; i < 30000; i++){}
}