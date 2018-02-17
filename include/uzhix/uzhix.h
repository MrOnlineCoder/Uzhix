/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _UZHIX_H
#define _UZHIX_H

#define UZHIX_VERSION "1.0.0"

#define asmv __asm__ __volatile__
#define asm __asm__

void panic(const char* msg);
void halt();

#endif
