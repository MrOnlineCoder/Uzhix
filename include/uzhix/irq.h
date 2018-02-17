/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _IRQ_H
#define _IRQ_H

#include <uzhix/io.h>

void irq_remove(unsigned short num);
void irq_set(unsigned short num,  void (*handler)(irq_registers_t *r));
void irq_install();

#endif
