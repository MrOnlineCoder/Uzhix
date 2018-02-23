/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _HEAP_H
#define _HEAP_H

#include <string.h>

#define HEAP_START 0x400000
#define HEAP_SIZE 0x100000
#define HEAP_FLAG_ALLOCATED 1
#define HEAP_FLAG_FREE 0

typedef struct {
  unsigned char* base;
  unsigned char* end;
} heap_t;

void* heap_alloc(heap_t* hp, size_t size);

void heap_free(heap_t* hp, void* ptr);

int heap_init(heap_t* target, unsigned int base, unsigned int size);

void heap_dump(heap_t* hp);

#endif
