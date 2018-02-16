/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/gdt.h>

struct gdt_entry gdt[3];

struct gdt_ptr gp;

void gdt_set_entry(short idx, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
  gdt[idx].base_low = (base & 0xFFFF);
  gdt[idx].base_middle = (base >> 16) & 0xFF;
  gdt[idx].base_high = (base >> 24) & 0xFF;

  gdt[idx].limit_low = (limit & 0xFFFF);
  gdt[idx].granularity = ((limit >> 16) & 0x0F);

  gdt[idx].granularity |= (gran & 0xF0);
  gdt[idx].access = access;
}

void gdt_install() {
  gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
  gp.base = (int) &gdt;

  gdt_set_entry(0, 0, 0, 0, 0);
	gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  gdt_load();
}
