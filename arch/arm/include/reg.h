#ifndef __REG_H_
#define __REG_H_
#include <stdint.h>

#define __REG_TYPE	volatile uint32_t
#define __REG		__REG_TYPE *
#define __CREG_TYPE volatile uint8_t
#define __CREG      __CREG_TYPE *     

#define SCS_BASE    (uint32_t) (0xE000E000)
#define SCB_BASE    (SCS_BASE + 0x0D00)
#define SCB_ICSR    ((__REG)(SCB_BASE + 0x04))
#define SCB_AIRCR   ((__REG)(SCB_BASE + 0x0C)) 
#define SCB_SHPR1   ((__REG)(SCB_BASE + 0x18)) 
#define SCB_SHPR2   ((__REG)(SCB_BASE + 0x1C)) 
#define SCB_SHPR3   ((__REG)(SCB_BASE + 0x20)) 

#define SCB_ICSR_PENDSVSET   (uint32_t) (1 << 28)

/* RCC Memory Map */
#define RCC_MAP		((__REG_TYPE) 0x40021000)
#define RCC_CR		((__REG) (RCC_MAP + 0x00))
#define RCC_CFGR	((__REG) (RCC_MAP + 0x04))
#define RCC_CIR		((__REG) (RCC_MAP + 0x08))
#define RCC_APB2RSTR	((__REG) (RCC_MAP + 0x0C))
#define RCC_APB1RSTR	((__REG) (RCC_MAP + 0x10))
#define RCC_AHBENR	((__REG) (RCC_MAP + 0x14))
#define RCC_APB2ENR	((__REG) (RCC_MAP + 0x18))
#define RCC_APB1ENR	((__REG) (RCC_MAP + 0x1C))
#define RCC_BDCR	((__REG) (RCC_MAP + 0x20))
#define RCC_CSR		((__REG) (RCC_MAP + 0x24))
#define RCC_CFGR	((__REG) (RCC_MAP + 0x04))
#define RCC_CFGR2	((__REG) (RCC_MAP + 0x2c))

/* Flash Memory Map */
#define FLASH_MMAP	((__REG_TYPE) 0x40022000)
#define FLASH_ACR	((__REG) (FLASH_MMAP + 0x00))

/* GPIO Memory Map */
#define GPIOA_MMAP	((__REG_TYPE) 0x40010800)
#define GPIOA_CRL	((__REG) (GPIOA_MMAP + 0x00))
#define GPIOA_CRH	((__REG) (GPIOA_MMAP + 0x04))
#define GPIOA_IDR	((__REG) (GPIOA_MMAP + 0x08))
#define GPIOA_ODR	((__REG) (GPIOA_MMAP + 0x0C))
#define GPIOA_BSRR	((__REG) (GPIOA_MMAP + 0x10))
#define GPIOA_BRR	((__REG) (GPIOA_MMAP + 0x14))
#define GPIOA_LCKR	((__REG) (GPIOA_MMAP + 0x18))

/* GPIO C */
#define GPIOC_MMAP	((__REG_TYPE) 0x40011000)
#define GPIOC_CRL	((__REG) (GPIOC_MMAP + 0x00))
#define GPIOC_CRH	((__REG) (GPIOC_MMAP + 0x04))
#define GPIOC_IDR	((__REG) (GPIOC_MMAP + 0x08))
#define GPIOC_ODR	((__REG) (GPIOC_MMAP + 0x0C))
#define GPIOC_BSRR	((__REG) (GPIOC_MMAP + 0x10))
#define GPIOC_BRR	((__REG) (GPIOC_MMAP + 0x14))
#define GPIOC_LCKR	((__REG) (GPIOC_MMAP + 0x18))


/* USART2 Memory Map */
#define USART2_MMAP	((__REG_TYPE) 0x40004400)
#define USART2_SR	((__REG) (USART2_MMAP + 0x00))
#define USART2_DR	((__REG) (USART2_MMAP + 0x04))
#define USART2_BRR	((__REG) (USART2_MMAP + 0x08))
#define USART2_CR1	((__REG) (USART2_MMAP + 0x0C))
#define USART2_CR2	((__REG) (USART2_MMAP + 0x10))
#define USART2_CR3	((__REG) (USART2_MMAP + 0x14))
#define USART2_GTPR	((__REG) (USART2_MMAP + 0x18))

struct USART_reg{
    __REG_TYPE SR;
    __REG_TYPE DR;
    __REG_TYPE BRR;
    __REG_TYPE CR1;
    __REG_TYPE CR2;
    __REG_TYPE CR3;
    __REG_TYPE GTPR;
};

#define pUSART1 ((struct USART_reg*)(0x40013800))
#define pUSART2 ((struct USART_reg*)(0x40004400))

/* SysTick Memory Map */
#define SYSTICK_MMAP	((__REG_TYPE) 0xE000E010)
#define SYSTICK_CTRL	((__REG) (SYSTICK_MMAP + 0x00))
#define SYSTICK_LOAD	((__REG) (SYSTICK_MMAP + 0x04))
#define SYSTICK_VAL	((__REG) (SYSTICK_MMAP + 0x08))
#define SYSTICK_CALIB	((__REG) (SYSTICK_MMAP + 0x0C))

struct NVIC_reg{
    uint32_t  ISER[3];
    uint32_t  ICER[3];
    uint32_t  ISPR[3];
    uint32_t  ICPR[3];
    uint32_t  IABR[3];
    uint32_t  IPR[21];
};

#define NVIC_MMAP    ((NVIC_reg *) 0x0xE000E100)
#define NVIC_STIP	 ((__REG) (0xE000EF00 + 0x0C))
#endif
