#include <stdint.h>
#include <arch.h>
#include <kernel.h>
#include <errno.h>
#include "pthread.h"


extern pthread_t pthread_next;
/* FIXME: Without naked attribute, GCC will corrupt r7 which is used for stack
 * pointer. If so, after restoring the tasks' context, we will get wrong stack
 * pointer.
 */
void __attribute__((naked)) pendsv_handler()
{
    asm volatile("cpsid i\n");
    asm volatile("mrs   r0, psp\n"
                 "stmdb r0!, {r4-r11, lr}\n");
    asm volatile("str  r0,%0\n" : "=m"(pthread_current));

    asm volatile("ldr r0, %0\n" : : "m" (pthread_next));
    asm volatile("ldmia r0!, {r4-r11}\n"
                 "msr psp, r0\n"
                 "orr lr,lr,0x04\n"
                 "cpsie i\n"
                 "bx lr\n");
}


void default_handler(void)
{
	while (1);
}

void nmi_handler(void) __attribute((weak, alias("default_handler")));
void hardfault_handler(void) __attribute((weak, alias("default_handler")));
void memmanage_handler(void) __attribute((weak, alias("default_handler")));
void busfault_handler(void) __attribute((weak, alias("default_handler")));
void usagefault_handler(void) __attribute((weak, alias("default_handler")));
void svc_handler(void) __attribute((weak, alias("default_handler")));
void systick_handler(void) __attribute((weak, alias("default_handler")));
void timer_update(void) __attribute((weak, alias("default_handler")));

__attribute((section(".isr_vector")))
uint32_t *isr_vectors[] = {
	[0x00] = (uint32_t *) &_estack,			/* stack pointer */
	[0x01] = (uint32_t *) _start,		/* code entry point */
	[0x02] = (uint32_t *) nmi_handler,		/* NMI handler */
	[0x03] = (uint32_t *) hardfault_handler,	/* hard fault handler */
	[0x04] = (uint32_t *) memmanage_handler,	/* mem manage handler */
	[0x05] = (uint32_t *) busfault_handler,		/* bus fault handler */
	[0x06] = (uint32_t *) usagefault_handler,	/* usage fault handler */
	[0x0B] = (uint32_t *) svc_handler,		/* svc handler */
	[0x0E] = (uint32_t *) pendsv_handler,		/* pendsv handler */
	[0x0F] = (uint32_t *) timer_update		/* systick handler */
};


