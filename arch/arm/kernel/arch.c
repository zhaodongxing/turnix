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

#define THREAD_PSP (0XFFFFFFFD)
#define PSR_THUMB  (0X01000000)

void arch_early_init(void)
{
    usart_init();
}

void switch_to_thread_mode(void){
    /* Save kernel context */
    asm volatile("mrs ip, psr\n"
                 "push {r4-r11, ip, lr}\n");


}

void arch_init(void)
{
    rcc_clock_init();
}

void arch_pthread_init(pthread_t th, void (*wrapper)(void *(*)(void *), void *),
		       void *(*start_routine)(void *), void *arg)
{
	unsigned long *stack;
	struct interrupt_context *ctx;

	stack = (unsigned long *)((char *)th->stack_addr + th->stack_size);
	ctx = (struct interrupt_context *)(stack - 1) - 1;
	ctx->r0 = (unsigned long)(arg);
    ctx->ip = (unsigned long)abort;
    ctx->pc = (unsigned long)start_routine;
	ctx->psr = (unsigned long)PSR_THUMB;
	th->context.sp = (unsigned long)ctx;
}
