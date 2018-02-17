/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/irq.h>
#include <uzhix/drivers/pic.h>
#include <uzhix/idt.h>

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void *handlers[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_handler(irq_registers_t* regs) {
  void (*handler)(irq_registers_t *r);

  handler = handlers[regs->int_no - 32];

  if (handler) {
      handler(regs);
  }

  if (regs->int_no >= 40){
    outb(SLAVE_PIC, 0x20);
  }

  outb(MASTER_PIC, 0x20);
}

void irq_remove(unsigned short num) {
  handlers[num] = 0;
}

void irq_set(unsigned short num, void (*handler)(irq_registers_t *r)) {
  handlers[num] = handler;
}

void irq_install() {
  pic_remap();

  idt_set_entry(32, (unsigned)irq0, 0x08, 0x8E);
  idt_set_entry(33, (unsigned)irq1, 0x08, 0x8E);
  idt_set_entry(34, (unsigned)irq2, 0x08, 0x8E);
  idt_set_entry(35, (unsigned)irq3, 0x08, 0x8E);
  idt_set_entry(36, (unsigned)irq4, 0x08, 0x8E);
  idt_set_entry(37, (unsigned)irq5, 0x08, 0x8E);
  idt_set_entry(38, (unsigned)irq6, 0x08, 0x8E);
  idt_set_entry(39, (unsigned)irq7, 0x08, 0x8E);
  idt_set_entry(40, (unsigned)irq8, 0x08, 0x8E);
  idt_set_entry(41, (unsigned)irq9, 0x08, 0x8E);
  idt_set_entry(42, (unsigned)irq10, 0x08, 0x8E);
  idt_set_entry(43, (unsigned)irq11, 0x08, 0x8E);
  idt_set_entry(44, (unsigned)irq12, 0x08, 0x8E);
  idt_set_entry(45, (unsigned)irq13, 0x08, 0x8E);
  idt_set_entry(46, (unsigned)irq14, 0x08, 0x8E);
  idt_set_entry(47, (unsigned)irq15, 0x08, 0x8E);
}
