/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _PIC_DRIVER_H
#define _PIC_DRVIER_H

#define MASTER_PIC		0x20
#define SLAVE_PIC		0xA0
#define MASTER_PIC_COMMAND	MASTER_PIC
#define MASTER_PIC_DATA	(MASTER_PIC+1)
#define SLAVE_PIC_COMMAND	SLAVE_PIC
#define SLAVE_PIC_DATA	(SLAVE_PIC+1)

void pic_remap();

#endif
