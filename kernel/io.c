/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/io.h>

#include <stdio.h>

void outb(unsigned short port, unsigned char data) {
	asmv ("outb %0,%1" : : "a" (data), "dN" (port));
}

unsigned char inb(unsigned short port) {
	unsigned char v;
  asmv ("inb %1,%0" : "=a" (v) : "dN" (port));
  return v;
}

void sti() {
	asmv("sti");
}

void cli() {
	asmv("cli");
}

void dump_registers(registers_t* regs) {
	register unsigned int eax asm("eax");
	register unsigned int ebx asm("ebx");
	register unsigned int ecx asm("ecx");
	register unsigned int edx asm("edx");
	register unsigned int esp asm("esp");
	
	unsigned int cr0;
	unsigned int cr3;

	asmv("mov %%cr0, %%eax; mov %%eax, %0;" : "=a" (cr0));
	asmv("mov %%cr3, %%eax; mov %%eax, %0;" : "=a" (cr3));

	regs->eax = eax;
	regs->ebx = ebx;
	regs->ecx = ecx;
	regs->edx = edx;
	regs->esp = esp;
	regs->cr0 = cr0;
	regs->cr3 = cr3;
}

void print_registers(registers_t* regs) {
	printf("EAX = %x, EBX = %x, ECX = %x, EDX = %x\n", regs->eax, regs->ebx, regs->ecx, regs->edx );
	printf("ESP = %x\n", regs->esp);
	printf("CR0 = %x CR3 = %x\n", regs->cr0, regs->cr3);
}
