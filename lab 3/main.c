#include "stm32f10x.h"
#define TIME_ON_MS 80
#define PERIOD_MS 1000
#define TIME_OFF_MS (PERIOD_MS - TIME_ON_MS)

volatile int timestamp = 0;

enum states {
    STATE_ON = TIME_OFF_MS,
    STATE_OFF = 0
};

void init();
void state_on();
void state_off();
void SysTick_Handler(void) {
    timestamp++;
}

int main(void) {
    init();
    while (1) {
        switch (timestamp % PERIOD_MS) {
            case STATE_ON:
                state_on();
                timestamp -= PERIOD_MS;
                break;
            case STATE_OFF:
                state_off();
                break;
        }
    }
}

void init() {
    RCC->APB2ENR = 0b1100; 
    GPIOB->CRH = 0x00000600; 
    GPIOA->CRL = 0x0000000C; 
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 900);
}

void state_on() {
    GPIOA->ODR = 0b1000000;
}

void state_off() {
    GPIOA->ODR = 0;
}