/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/gdt.h>
#include <uzhix/drivers/screen.h>

#include <stdio.h>

void kernel_main() {

  gdt_install();

  screen_init();
  printf("Hello World!\n");

  for (;;);
}
