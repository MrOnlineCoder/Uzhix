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
#include <uzhix/mm/heap.h>
#include <uzhix/mm/paging.h>

#include <stdio.h>
#include <stdlib.h>

void kernel_main() {
  cli();
  screen_init();

  printf("* Uzhix ver.%s *\n\n", UZHIX_VERSION);

  printf("Installing GDT...\n");
  gdt_install();

  printf("Installing IDT and handlers... \n");
  idt_install();
  isr_install_exceptions();
  irq_install();

  printf("Initializing kernel heap... \n");
  kernel_heap_init();

  printf("Identity mapping the first 4MB... \n");
  paging_identity_map_kernel();

  printf("Enabling paging...\n");
  paging_enable();

  cmos_time tm;
  cmos_get_time(&tm);
  printf("CMOS time is: %d:%d:%d %d.%d.%d\n", tm.hours, tm.minutes, tm.seconds, tm.dayofmonth, tm.month, tm.year);

  printf("\n");

  panic("failed to start init task");
}
