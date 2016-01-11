#include "reg.h"

/* Bit definition for RCC_CR register */
#define RCC_CR_HSION	((uint32_t) 0x00000001)		/*!< Internal High Speed clock enable */
#define RCC_CR_HSEON	((uint32_t) 0x00010000)		/*!< External High Speed clock enable */
#define RCC_CR_HSERDY	((uint32_t) 0x00020000)		/*!< External High Speed clock ready flag */
#define RCC_CR_CSSON	((uint32_t) 0x00080000)		/*!< Clock Security System enable */

/* Bit definition for RCC_CFGR register */
#define  RCC_CFGR_SW		((uint32_t) 0x00000003)	/*!< SW[1:0] bits (System clock Switch) */
#define  RCC_CFGR_SW_PLL	((uint32_t) 0x00000002)	/*!< HSE selected as system clock */
#define  RCC_CFGR_SWS		((uint32_t) 0x0000000C)	/*!< SWS[1:0] bits (System Clock Switch Status) */
#define  RCC_CFGR_HPRE_DIV1	((uint32_t) 0x00000000)	/*!< SYSCLK not divided */
#define  RCC_CFGR_PPRE1_DIV1	((uint32_t) 0x00000400)	/*!< HCLK divided by 2 , 36MHZ*/
#define  RCC_CFGR_PPRE2_DIV1	((uint32_t) 0x00000000)	/*!< HCLK not divided 72MHZ*/
#define  RCC_CFGR_PLL_SRC       ((uint32_t) 0x00010000) /*!< CLOCK from PREDIV1*/
#define  RCC_CFGR_PLL_MUL       ((uint32_t) 0x001C0000) /*!< PLL input clock x 9*/
#define  RCC_CFGR2_PREDIV1SRC   ((uint32_t) 0x00000000) /*HSE oscillator clock selected as PREDIV1 clock entry*/
#define  RCC_CR_PLL_ENABLE      ((uint32_t) 0x01000000)

/* Bit definition for FLASH_ACR register */
#define FLASH_ACR_LATENCY	((uint8_t) 0x03)	/*!< LATENCY[2:0] bits (Latency) */
#define FLASH_ACR_LATENCY_0	((uint8_t) 0x00)	/*!< Bit 0 */
#define FLASH_ACR_LATENCY_2	((uint8_t) 0x02)	/*!< Bit 0 */
#define FLASH_ACR_PRFTBE	((uint8_t) 0x10)	/*!< Prefetch Buffer Enable */

#define HSE_STARTUP_TIMEOUT	((uint16_t) 0x0500)	/*!< Time out for HSE start up */


void rcc_clock_init(void)
{
	/* Reset the RCC clock configuration to the default reset state(for debug purpose) */
	/* Set HSION bit */
	*RCC_CR |= (uint32_t) 0x00000001;

	/* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
	*RCC_CFGR &= (uint32_t) 0xF8FF0000;

	/* Reset HSEON, CSSON and PLLON bits */
	*RCC_CR &= (uint32_t) 0xFEF6FFFF;

	/* Reset HSEBYP bit */
	*RCC_CR &= (uint32_t) 0xFFFBFFFF;

	/* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
	*RCC_CFGR &= (uint32_t) 0xFF80FFFF;

	/* Disable all interrupts and clear pending bits  */
	*RCC_CIR = 0x009F0000;

	/* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
	/* Configure the Flash Latency cycles and enable prefetch buffer */
	volatile uint32_t StartUpCounter = 0, HSEStatus = 0;

	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
	/* Enable HSE */
	*RCC_CR |= ((uint32_t)RCC_CR_HSEON);

	/* Wait till HSE is ready and if Time out is reached exit */
	do {
		HSEStatus = *RCC_CR & RCC_CR_HSERDY;
		StartUpCounter++;
	} while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((*RCC_CR & RCC_CR_HSERDY) != 0)
		HSEStatus = (uint32_t) 0x01;
	else
		HSEStatus = (uint32_t) 0x00;

	if (HSEStatus == (uint32_t) 0x01) {
		/* Enable Prefetch Buffer */
		*FLASH_ACR |= FLASH_ACR_PRFTBE;

		/* Flash 0 wait state */
		*FLASH_ACR &= (uint32_t)((uint32_t) ~FLASH_ACR_LATENCY);

		*FLASH_ACR |= (uint32_t) FLASH_ACR_LATENCY_2;

        *RCC_CFGR2 |= (uint32_t) RCC_CFGR2_PREDIV1SRC;

		*RCC_CFGR |= (uint32_t) RCC_CFGR_PLL_SRC;

		*RCC_CFGR |= (uint32_t) RCC_CFGR_PLL_MUL;

		/* HCLK = SYSCLK 72M*/
		*RCC_CFGR |= (uint32_t) RCC_CFGR_HPRE_DIV1;

		/* PCLK2 = HCLK 72M*/
		*RCC_CFGR |= (uint32_t) RCC_CFGR_PPRE2_DIV1;

		/* PCLK1 = HCLK/2 36M*/
		*RCC_CFGR |= (uint32_t) RCC_CFGR_PPRE1_DIV1;

        *RCC_CR   |= RCC_CR_PLL_ENABLE;

        while((*RCC_CR&0x02000000) != 0x02000000);

		/* Select HSE as system clock source */
		*RCC_CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_SW));
		*RCC_CFGR |= (uint32_t) RCC_CFGR_SW_PLL;

		/* Wait till PLL is used as system clock source */
		while ((*RCC_CFGR & (uint32_t) RCC_CFGR_SWS) != (uint32_t) 0x08);
	} else {
		/* If HSE fails to start-up, the application will have wrong clock
		configuration. User can add here some code to deal with this error */
	}
}
