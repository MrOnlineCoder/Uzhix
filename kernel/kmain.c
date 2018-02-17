/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/drivers/screen.h>

#include <uzhix/gdt.h>
#include <uzhix/idt.h>
#include <uzhix/irq.h>
#include <uzhix/isr.h>

#include <uzhix/io.h>
#include <uzhix/uzhix.h>
#include <uzhix/drivers/cmos.h>

#include <stdio.h>

void kernel_main() {
  cli();
  screen_init();

  printf("* Uzhix ver.%s *\n", UZHIX_VERSION);

  printf("installing GDT...\n");
  gdt_install();

  printf("installing IDT and handlers...\n");
  idt_install();
  isr_install_exceptions();
  irq_install();

  printf("enabling interrupts...\n");
  sti();

  cmos_time tm;
  cmos_get_time(&tm);
  printf("%d:%d:%d %d.%d.%d\n", tm.hours, tm.minutes, tm.seconds, tm.dayofmonth, tm.month, tm.year);

  panic("bye");
}
