#ifndef __REG_H_
#define __REG_H_
#include <stdint.h>

#define REG	volatile uint32_t

struct SCB_reg{
	REG CPUID;
	REG ICSR;
	REG VTOR;
	REG AIRCR;
	REG SCR;
	REG CCR;
	REG SHPR1;
	REG SHPR2;
	REG SHPR3;
};



struct RCC_reg{
	REG CR;
	REG CFGR;
	REG CIR;
	REG APB2RSTR;
	REG APB1RSTR;
	REG AHBENR;
	REG APB2ENR;
	REG APB1ENR;
	REG BDCR;
	REG CSR;
	REG PAD;
	REG CFGR2;
};

struct FLASH_reg{
	REG ACR;
};

struct GPIO_reg{
	REG CRL;
	REG CRH;
	REG IDR;
	REG ODR;
	REG BSRR;
	REG BRR;
	REG LCKR;
};

struct USART_reg{
    REG SR;
    REG DR;
    REG BRR;
    REG CR1;
    REG CR2;
    REG CR3;
    REG GTPR;
};

struct SYSTICK_reg{
	REG CTRL;
	REG LOAD;
	REG VAL;
	REG CALIB;
};

struct NVIC_reg{
    REG  ISER[3];
    REG  ICER[3];
    REG  ISPR[3];
    REG  ICPR[3];
    REG  IABR[3];
    REG  IPR[21];
};

#define pGPIOA     ((struct GPIO_reg*)(0x40010800))
#define pGPIOC     ((struct GPIO_reg*)(0x40011000))
#define pSYSTICK   ((struct SYSTICK_reg*)(0xE000E010))
#define pUSART1    ((struct USART_reg*)(0x40013800))
#define pUSART2    ((struct USART_reg*)(0x40004400))
#define pRCC       ((struct RCC_reg*)(0x40021000))
#define pFLASH     ((struct FLASH_reg*)(0x40022000))
#define pSCB       ((struct SCB_reg*)(0xE000ED00))

#define NVIC_MMAP    ((NVIC_reg *) 0x0xE000E100)
#define NVIC_STIP	 ((__REG) (0xE000EF00 + 0x0C))
#endif
