#include <stdint.h>
#include <arch.h>
#include <kernel.h>
#include <errno.h>
#include <NVIC.h>
#include <timer.h>
#include "pthread.h"


extern pthread_t pthread_next;

void interrupt_init(void){
    /*init interrupt priority group config
     * 8 group priority 2 sub priority */
    *SCB_AIRCR=(*SCB_AIRCR&0xfffff8ff)|(0x4<<8);
    *SCB_SHPR3=(uint32_t)0xEFFF0000;
    
}

/*interrupt use msp*/
void pendsv_handler(void)
{
    asm volatile("cpsid i\n"
                 "mrs   r0, psp\n"
                 "stmdb r0!, {r4-r11}\n"
                 "mov r1,%0\n"
                 "str r0,[r1]\n": :"r"(pthread_current));
    pthread_current = pthread_next;
    asm volatile("mov r0, %0\n"
                 "ldr r1, [r0]\n"
                 "ldmia r1!, {r4-r11}\n"
                 "msr psp, r1\n"
                 "orr lr,lr,0x04\n"
                 "cpsie i\n"
                 "bx lr": :"r"(pthread_current));
}


void default_handler(void)
{
	while (1);
}

void hardfault_handler(void)
{
	while (1);
}

void nmi_handler(void) __attribute((weak, alias("default_handler")));
void memmanage_handler(void) __attribute((weak, alias("default_handler")));
void busfault_handler(void) __attribute((weak, alias("default_handler")));
void usagefault_handler(void) __attribute((weak, alias("default_handler")));
void svc_handler(void) __attribute((weak, alias("default_handler")));


__attribute((section(".isr_vector")))
struct NVIC_table isr = {
    .stack     = (uint32_t)&_estack,
    .Reset     = (uint32_t)__start,
    .NMI       = (uint32_t)nmi_handler,
    .HardFault = (uint32_t)hardfault_handler,
    .MemManage = (uint32_t)memmanage_handler,
    .PendSV    = (uint32_t)pendsv_handler,
    .SysTick   = (uint32_t)timer_update,
};


