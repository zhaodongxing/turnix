#include <stdint.h>
#include <arch.h>
#include <kernel.h>
#include <errno.h>
#include <NVIC.h>
#include <timer.h>
#include "pthread.h"

void interrupt_init(void){
    /*init interrupt priority group config
     * 8 group priority 2 sub priority */
    pSCB->AIRCR=(pSCB->AIRCR&0xfffff8ff)|(0x4<<8);
    pSCB->SHPR3=(uint32_t)0xEFFF0000;
    
}

void default_handler(void)
{
	while (1);
}

void nmi_handler(void) __attribute((weak, alias("default_handler")));
void memmanage_handler(void) __attribute((weak, alias("default_handler")));
void busfault_handler(void) __attribute((weak, alias("default_handler")));
void usagefault_handler(void) __attribute((weak, alias("default_handler")));
void svc_handler(void) __attribute((weak, alias("default_handler")));
void hardfault_handler(void) __attribute((weak, alias("default_handler")));


__attribute((section(".isr_vector")))
struct NVIC_table isr = {
    .stack     = (uint32_t)&_estack,
    .Reset     = (uint32_t)start,
    .NMI       = (uint32_t)nmi_handler,
    .HardFault = (uint32_t)hardfault_handler,
    .MemManage = (uint32_t)memmanage_handler,
    .PendSV    = (uint32_t)pendsv_handler,
    .SysTick   = (uint32_t)timer_update,
};


