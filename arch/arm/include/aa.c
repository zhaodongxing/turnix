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

static unsigned long interrupt_disable(void)
{
    unsigned long flags;
    asm volatile("mrs %0,primask\n"
                 "cpsid i\n":"=r"(flags));
    return flags;
}
static void interrupt_enable(unsigned long flags)
{
    asm volatile("msr primask,%0\n"::"r"(flags));
}

static int atomic_add_return(int v, volatile int *ptr)
{
	int retval = v;

	asm volatile("retry:ldrex r4, %1\n" 
	             "add r4,r4,%2\n"
                 "strex r5,r4,%0\n"
                 "cmp r5,#0\n"
                 "ite eq\n"
                 "streq r4,%0\n"
                 "bne retry\n"
                 : "=m"(*ptr)
                 : "m"(*ptr),"r"(retval)
                 : "r4","r5");
	return retval;
}

