/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/idt.h>
#include <string.h>

struct idt_ptr idtp;
struct idt_entry idt[256];

void idt_install() {
  idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
  idtp.base = (unsigned int) &idt;

  memset(&idt, 0, sizeof(struct idt_entry) * 256 - 1);

  idt_load();
}

void idt_set_entry(int idx, unsigned long base, unsigned short sel, unsigned char flags) {
  idt[idx].base_low = (base & 0xFFFF);
  idt[idx].base_high = (base >> 16) & 0xFFFF;

  idt[idx].sel = sel;
  idt[idx].zero = 0;
  idt[idx].flags = flags;
}
