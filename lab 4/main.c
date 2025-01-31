#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

int timer = 0;

int main(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    TIM_TimeBaseInitTypeDef InitTIM;
    NVIC_InitTypeDef        InitNVIC;
    InitTIM.TIM_Prescaler = 16; 
    InitTIM.TIM_Period = 8;
    InitTIM.TIM_ClockDivision = TIM_CKD_DIV1;
    InitTIM.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, & InitTIM);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);

    InitNVIC.NVIC_IRQChannel = TIM2_IRQn;
    InitNVIC.NVIC_IRQChannelPreemptionPriority = 0x00;
    InitNVIC.NVIC_IRQChannelSubPriority = 0x00;
    InitNVIC.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&InitNVIC);

    while (1) {
        GPIO_SetBits(GPIOB, GPIO_Pin_8);
        delay(300);
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);
        delay(300);
    }
}

void TIM2_IRQHandler()
{
    timer++; 
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void delay(int period)
{
    while(timer < period){}
    timer = 0;
}