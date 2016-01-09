#include <arch.h>

void led_init(){
    *(RCC_APB2ENR) |= 0x00000010;
    *GPIOC_CRH = 0x00300000;
}

inline void led_on(){
    *GPIOC_BSRR = 0x00002000;
}

inline void led_off(){
    *GPIOC_BSRR = 0x20000000;
}
