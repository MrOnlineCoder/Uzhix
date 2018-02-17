/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/drivers/pic.h>
#include <uzhix/io.h>

void pic_remap() {
  outb(MASTER_PIC, 0x11);
  outb(SLAVE_PIC, 0x11);
  outb(MASTER_PIC_DATA, 0x20);
  outb(SLAVE_PIC_DATA, 0x28);
  outb(MASTER_PIC_DATA, 0x04);
  outb(SLAVE_PIC_DATA, 0x02);
  outb(MASTER_PIC_DATA, 0x01);
  outb(SLAVE_PIC_DATA, 0x01);
  outb(MASTER_PIC_DATA, 0x0);
  outb(SLAVE_PIC_DATA, 0x0);
}
