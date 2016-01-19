#include <reg.h>
#include <arch.h>
/* 72MHz */
#define CPU_CLOCK_HZ 72000000
/* 100 ms per tick. */
#define TICK_RATE_HZ 100

void timer_init(void)
{
	/* SysTick configuration */
	pSYSTICK->CTRL = (CPU_CLOCK_HZ / TICK_RATE_HZ) - 1UL;
	pSYSTICK->VAL = 0;
	pSYSTICK->CTRL = 0x07;
}
