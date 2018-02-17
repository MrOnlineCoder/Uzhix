/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/io.h>
#include <uzhix/idt.h>

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

char* exceptions[] = {
	"DIVISION_BY_ZERO", /* 0 */
	"DEBUG_EXCEPTION", /* 1 */
	"RESERVED", /* 2 */
	"BREAKPOINT", /* 3 */
	"OVERFLOW", /* 4 */
	"BOUNDS_CHECK", /* 5 */
	"INVALID_OPCODE", /* 6 */
	"COPROC_NOT_AVALIABLE", /* 7 */
	"DOUBLE_FAULT", /* 8 */
	"COPROC_SEGMENT_OVERRUN", /* 9 */
	"INVALID_TSS", /* 10 */
	"SEGMENT_NOT_PRESENT", /* 11 */
	"STACK_EXCEPTION", /* 12 */
	"TRIPLE_FAULT", /* 13 */
	"PAGE_FAULT", /* 14 */
	"RESERVED", /* 15 */
	"COPROC_ERROR" /* 16 */
};

void isr_exception(int n) {
	cli();

	panic(exceptions[n]);
}

void isr_install_exceptions(){
    idt_set_entry(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_entry(1, (unsigned)isr1, 0x08, 0x8E);
    idt_set_entry(2, (unsigned)isr2, 0x08, 0x8E);
    idt_set_entry(3, (unsigned)isr3, 0x08, 0x8E);
    idt_set_entry(4, (unsigned)isr4, 0x08, 0x8E);
    idt_set_entry(5, (unsigned)isr5, 0x08, 0x8E);
    idt_set_entry(6, (unsigned)isr6, 0x08, 0x8E);
    idt_set_entry(7, (unsigned)isr7, 0x08, 0x8E);
    idt_set_entry(8, (unsigned)isr8, 0x08, 0x8E);
    idt_set_entry(9, (unsigned)isr9, 0x08, 0x8E);
    idt_set_entry(10, (unsigned)isr10, 0x08, 0x8E);
    idt_set_entry(11, (unsigned)isr11, 0x08, 0x8E);
    idt_set_entry(12, (unsigned)isr12, 0x08, 0x8E);
    idt_set_entry(13, (unsigned)isr13, 0x08, 0x8E);
    idt_set_entry(14, (unsigned)isr14, 0x08, 0x8E);
    idt_set_entry(15, (unsigned)isr15, 0x08, 0x8E);
    idt_set_entry(16, (unsigned)isr16, 0x08, 0x8E);
    idt_set_entry(17, (unsigned)isr17, 0x08, 0x8E);
    idt_set_entry(18, (unsigned)isr18, 0x08, 0x8E);
    idt_set_entry(19, (unsigned)isr19, 0x08, 0x8E);

    idt_set_entry(20, 0, 0x08, 0x8E);
    idt_set_entry(21, 0, 0x08, 0x8E);
    idt_set_entry(22, 0, 0x08, 0x8E);
    idt_set_entry(23, 0, 0x08, 0x8E);
    idt_set_entry(24, 0, 0x08, 0x8E);
    idt_set_entry(25, 0, 0x08, 0x8E);
    idt_set_entry(26, 0, 0x08, 0x8E);
    idt_set_entry(27, 0, 0x08, 0x8E);
    idt_set_entry(28, 0, 0x08, 0x8E);
    idt_set_entry(29, 0, 0x08, 0x8E);
    idt_set_entry(30, 0, 0x08, 0x8E);
    idt_set_entry(31, 0, 0x08, 0x8E);
}
