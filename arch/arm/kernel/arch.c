/*
 * Copyright (c) 2015 Changli Gao <xiaosuo@gmail.com>
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <arch.h>
#include <pthread.h>
#include <kernel.h>
#include <hw_init.h>
static __attribute__((section(".data.idle"))) __attribute((used)) int idle_stack[25];

#define THREAD_PSP (0XFFFFFFFD)
#define PSR_THUMB  (0X01000000)

void __start(void)
{
	/* Copy the data segment initializers from flash to SRAM */
	uint32_t *idata_begin = &_sidata;
	uint32_t *data_begin = &_sdata;
	uint32_t *data_end = &_edata;
	while (data_begin < data_end) *data_begin++ = *idata_begin++;

	/* Zero fill the bss segment. */
	uint32_t *bss_begin = &_sbss;
	uint32_t *bss_end = &_ebss;
	while (bss_begin < bss_end) *bss_begin++ = 0;

	main();
}

void arch_early_init(void)
{
    rcc_clock_init();
    interrupt_init();
    usart_init();
    timer_init();
}

int atomic_add_return(int v, volatile int *ptr)
{
    asm volatile("again: ldrex r4, %1\n" 
	             "add r4,r4,%2\n"
                 "strex r5,r4,%0\n"
                 "cmp r5,#0\n"
                 "ite eq\n"
                 "streq r4,%0\n"
                 "bne again\n"
                 : "=m"(*ptr)
                 : "m"(*ptr),"r"(v)
                 : "r4","r5");
	return 0;
}


void arch_init(void)
{
    /*start to use psp*/
    asm volatile("msr psp,%0\n"
                 "mov r1,0x02\n"
                 "msr control,r1\n": :"r"(_edata));
}

void arch_pthread_init(pthread_t th, void (*wrapper)(void *(*)(void *), void *),
		               void *(*start_routine)(void *), void *arg)
{
	uint32_t *stack;
	struct interrupt_context *ctx;

	stack = (uint32_t *)(th->stack_addr + th->stack_size);
	ctx = (struct interrupt_context *)(stack) - 1;
	ctx->r0 = (uint32_t)(start_routine);
	ctx->r1 = (uint32_t)arg;
	ctx->r2 = (uint32_t)(0x02020202);
	ctx->r3 = (uint32_t)(0x03030303);
    ctx->r4 = (uint32_t)(0x04040404);
    ctx->r5 = (uint32_t)(0x05050505);
    ctx->r6 = (uint32_t)(0x06060606);
    ctx->lr = (uint32_t)abort;
    ctx->pc = (uint32_t)wrapper;
	ctx->psr = (uint32_t)PSR_THUMB;
	th->context.sp = (uint32_t)ctx;
}

void reboot(void){
    *SCB_AIRCR|=0x4;
}
