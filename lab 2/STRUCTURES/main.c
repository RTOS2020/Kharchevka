#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void delay();

int main(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= 0;
    GPIOC->CRH |= GPIO_CRH_MODE;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL &= 0;
    GPIOA->CRL |= GPIO_CRL_MODE;

    while (1) {
        GPIOC->ODR ^= GPIO_Pin_13;
        GPIOA->ODR = GPIO_Pin_4;
        delay();
        GPIOA->ODR ^= GPIO_Pin_4;
        delay();
        GPIOC->ODR = GPIO_Pin_13;
        GPIOA->ODR = GPIO_Pin_4;
        delay();
        GPIOA->ODR ^= GPIO_Pin_4;
        delay();

    }
}

void delay(void) {
    for (int i = 0; i < 30000; i++) {}
}
