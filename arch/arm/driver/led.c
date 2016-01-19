#include <arch.h>

void led_init(){
    pRCC->APB2ENR |= 0x00000010;
    pGPIOC->CRH = 0x00300000;
}

inline void led_on(){
    pGPIOC->BSRR = 0x00002000;
}

inline void led_off(){
    pGPIOC->BSRR = 0x20000000;
}

void led_alert(){
	led_on();
	while(1); //forever loop
}
