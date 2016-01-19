#include <reg.h>

/* Bit definition for FLASH_ACR register */
#define FLASH_ACR_LATENCY	((uint8_t) 0x03)	/*!< LATENCY[2:0] bits (Latency) */
#define FLASH_ACR_LATENCY_0	((uint8_t) 0x00)	/*!< Bit 0 */
#define FLASH_ACR_LATENCY_2	((uint8_t) 0x02)	/*!< Bit 0 */
#define FLASH_ACR_PRFTBE	((uint8_t) 0x10)	/*!< Prefetch Buffer Enable */

void flash_init(void){
    /* Enable Prefetch Buffer */
    pFLASH->ACR |= FLASH_ACR_PRFTBE;
	/* Flash 0 wait state */
	pFLASH->ACR &= (uint32_t)((uint32_t) ~FLASH_ACR_LATENCY);
	pFLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_2;
}
