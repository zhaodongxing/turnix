#ifndef HW_INIT_H
#define HW_INIT_H

void rcc_clock_init(void);
void usart_init(void);
void timer_init(void);
void flash_init(void);
void led_init();
void led_on();
void led_off();
void led_alert();

#endif
