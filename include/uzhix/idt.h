/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _IDT_H
#define _IDT_H

struct idt_entry {
   unsigned short base_low; // offset bits 0..15
   unsigned short sel; // a code segment selector in GDT or LDT
   unsigned char zero;
   unsigned char flags;
   unsigned short base_high;
}  __attribute__((packed));

struct idt_ptr {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

extern void idt_load();

void idt_install();
void idt_set_entry(int idx, unsigned long base, unsigned short sel, unsigned char flags);

#endif
