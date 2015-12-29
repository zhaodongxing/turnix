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

#define THREAD_PSP (0XFFFFFFFD)
#define PSR_THUMB  (0X01000000)

void arch_early_init(void)
{
    rcc_clock_init();
    usart_init();
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


void switch_to_thread_mode(void){
    /* Save kernel context */
    asm volatile("mrs ip, psr\n"
                 "push {r4-r11, ip, lr}\n");


}

void arch_init(void)
{
}

void arch_pthread_init(pthread_t th, void (*wrapper)(void *(*)(void *), void *),
		               void *(*start_routine)(void *), void *arg)
{
	unsigned long *stack;
	struct interrupt_context *ctx;

	stack = (unsigned long *)(th->stack_addr + th->stack_size);
	ctx = (struct interrupt_context *)(stack) - 1;
	ctx->r0 = (unsigned long)(arg);
	ctx->r1 = (unsigned long)(0x01010101);
	ctx->r2 = (unsigned long)(0x02020202);
	ctx->r3 = (unsigned long)(0x03030303);
    ctx->r4 = (unsigned long)(0x04040404);
    ctx->r5 = (unsigned long)(0x05050505);
    ctx->r6 = (unsigned long)(0x06060606);
    ctx->lr = (unsigned long)abort;
    ctx->pc = (unsigned long)start_routine;
	ctx->psr = (unsigned long)PSR_THUMB;
    printf("ctx addr is %x start %x\n",ctx,ctx->pc);
	th->context.sp = (unsigned long)ctx;
}

void reboot(void){
    *SCB_AIRCR|=0x4;
}
