#ifndef NVIC_H
#define NVIC_H

struct NVIC_table {
    uint32_t stack;
    uint32_t Reset;
    uint32_t NMI;
    uint32_t HardFault;
    uint32_t MemManage;
    uint32_t BusFault;
    uint32_t UsageFault;
    uint32_t reserve[4];
    uint32_t SVCall;
    uint32_t DebugMonitor;
    uint32_t reserve1;
    uint32_t PendSV;
    uint32_t SysTick;
    uint32_t WWDG;
    uint32_t PVD;
    uint32_t TAMPER;
    uint32_t RTC;
    uint32_t FLASH;
    uint32_t RCC;
    uint32_t EXTI[5];
    uint32_t DMA1_Channel[7];
    uint32_t ADC1_2;
    uint32_t CAN1[4];
    uint32_t EXTI9_5;
    uint32_t TIM1[4];
    uint32_t TIM2;
    uint32_t TIM3;
    uint32_t TIM4;
    uint32_t I2C1[4];
    uint32_t SPI[2];
    uint32_t USART1;
    uint32_t USART2;
    uint32_t USART3;
};

void __attribute__((naked)) pendsv_handler();
#endif
