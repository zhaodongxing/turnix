/* main program entry point */
extern void main(void);

/* start address for the initialization values of the .data section.
 * defined in linker script */
extern uint32_t _sidata;
/* start address for the .data section. defined in linker script */
extern uint32_t _sdata;
/* end address for the .data section. defined in linker script */
extern uint32_t _edata;
/* start address for the .bss section. defined in linker script */
extern uint32_t _sbss;
/* end address for the .bss section. defined in linker script */
extern uint32_t _ebss;
/* end address for the stack. defined in linker script */
extern uint32_t _estack;


/* FIXME: Without naked attribute, GCC will corrupt r7 which is used for stack
 * pointer. If so, after restoring the tasks' context, we will get wrong stack
 * pointer.
 */
void __attribute__((naked)) pendsv_handler()
{
    /* Save the old task's context */
    asm volatile("mrs   r0, psp\n"
                 "stmdb r0!, {r4-r11, lr}\n");
    /* To get the task pointer address from result r0 */
    asm volatile("mov   %0, r0\n" : "=r" (tasks[lastTask].stack));

    /* Find a new task to run */
    while (1) {
        lastTask++;
        if (lastTask == MAX_TASKS)
            lastTask = 0;
        if (tasks[lastTask].in_use) {
            /* Move the task's stack pointer address into r0 */
            asm volatile("mov r0, %0\n" : : "r" (tasks[lastTask].stack));
            /* Restore the new task's context and jump to the task */
            asm volatile("ldmia r0!, {r4-r11, lr}\n"
                         "msr psp, r0\n"
                         "bx lr\n");
        }
    }
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
void pendsv_handler(void) __attribute((weak, alias("default_handler")));
void systick_handler(void) __attribute((weak, alias("default_handler")));

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


