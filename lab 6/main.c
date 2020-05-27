#include "STM32F10x.h"
#include <cmsis_os.h>
#include "STM32F10x_gpio.h"
#include "STM32F10x_rcc.h"

void delay(int ms) {
    for (int i = 0; i < 3000 * ms; i++) {}
}

void led_thread1(void const *argument) 
{
    for (;;) {
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        delay(200);
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        delay(200);
    }
}

void led_thread2(void const *argument) 

{
    for (;;) {
        GPIO_SetBits(GPIOA, (GPIO_Pin_1));
        delay(400);
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        delay(400);
    }
}
osThreadId main_ID, led_ID1, led_ID2, led_ID3;
osThreadDef(led_thread2, osPriorityNormal,1, 0);
osThreadDef(led_thread1, osPriorityNormal,1, 0);

int main(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_StructInit(&LAB_6_GPIO_A);
    LAB_6_GPIO_A.GPIO_Pin =
            GPIO_Pin_0 |
            GPIO_Pin_1;
    LAB_6_GPIO_A.GPIO_Mode = GPIO_Mode_Out_PP;
    LAB_6_GPIO_A.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &LAB_6_GPIO_A);
    osKernelInitialize();                    
    led_ID1 = osThreadCreate(osThread(led_thread1), NULL);
    led_ID2 = osThreadCreate(osThread(led_thread2), NULL);
    osKernelStart();                         
    while (1) { ; }
}
