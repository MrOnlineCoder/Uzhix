/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _UZHIX_IO_H
#define _UZHIX_IO_H

#include <uzhix/uzhix.h>

typedef struct {
  unsigned int gs, fs, es, ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip, cs, eflags, useresp, ss;
} irq_registers_t;

typedef struct {
  unsigned int eax, ebx, ecx, edx;
  unsigned int cr0, cr3;
  unsigned int esp;
} registers_t;

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

void sti();
void cli();

void dump_registers(registers_t* regs);
void print_registers(registers_t* regs);

#endif
