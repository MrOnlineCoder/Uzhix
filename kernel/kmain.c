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

#include <stdio.h>
#include <stdlib.h>

void kernel_main() {
  cli();
  screen_init();

  printf("* Uzhix ver.%s *\n\n", UZHIX_VERSION);

  printf("Installing GDT -> ");
  gdt_install();
  printf("OK\n");

  printf("Installing IDT and handlers -> ");
  idt_install();
  isr_install_exceptions();
  irq_install();
  printf("OK\n");

  printf("Initializing kernel heap -> ");
  kernel_heap_init();
  printf("OK\n");

  cmos_time tm;
  cmos_get_time(&tm);
  printf("System time is: %d:%d:%d %d.%d.%d\n", tm.hours, tm.minutes, tm.seconds, tm.dayofmonth, tm.month, tm.year);

  kernel_heap_dump();

  unsigned char* ptr = kernel_heap_alloc(4);
  unsigned char* ptr2 = kernel_heap_alloc(1024);
  ptr[0] = 'H';
  ptr[1] = 'I';
  ptr[2] = '\0';

  kernel_heap_dump();
  kernel_heap_free(ptr);
  kernel_heap_free(ptr2);
  kernel_heap_dump();
  printf("%s\n", ptr);

  printf("\n");

  panic("failed to start init task");
}
