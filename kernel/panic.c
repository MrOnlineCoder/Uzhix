/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/io.h>
#include <uzhix/uzhix.h>
#include <uzhix/drivers/screen.h>

#include <stdio.h>

void halt() {
  for(;;) {
    asm("hlt");
 }
}

void panic(const char* msg) {
  cli();

  printf("\n");

  registers_t regs;
  dump_registers(&regs);
  print_registers(&regs);

  screen_set_color(SCREEN_COLOR_WHITE, SCREEN_COLOR_RED);

  printf("  kernel panic: %s\n", msg);

  halt();
}
