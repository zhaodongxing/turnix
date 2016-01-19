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
#ifndef _ARCH_H_
#define _ARCH_H_

#include <stdint.h>
#include <reg.h>
#include <arch.h>
#include <stdio.h>
#define SCB_ICSR_PENDSVSET   (uint32_t) (1 << 28)

static inline void arch_context_switch(void)
{
    pSCB->ICSR |= SCB_ICSR_PENDSVSET;
    asm volatile("mrs r0,primask\n"
                 "cpsie i\n"
                 "msr primask,r0\n");
}

static inline void arch_halt(void)
{
}


struct interrupt_context {
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t ip;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;
};

struct arch_context{
    unsigned long sp;
};

void start(void);
void arch_early_init();
void arch_init();
void arch_enable_interrupt();
void interrupt_init();
void reboot(void);
int  atomic_add_return(int v, volatile int *ptr);
unsigned long interrupt_disable(void);
void interrupt_enable(unsigned long flags);


#endif

