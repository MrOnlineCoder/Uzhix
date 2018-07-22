/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _LIBC_STDLIB_H
#define _LIBC_STDLIB_H

#include <string.h>

#define NULL  ((void *) 0)

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void* ptr, size_t size);

#endif
