/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _HEAP_H
#define _HEAP_H

#include <string.h>

#define MAKE_WORD(byte1, byte2) (unsigned short) ((byte1 << 8) + (byte2 & 0xFF))

#define WORD_HIGH(word) (unsigned char) ((word >> 8) & 0xFF)
#define WORD_LOW(word) (unsigned char) (word & 0xFF)

#define KERNEL_HEAP_START 0x300000 // 3 Mb
#define KERNEL_HEAP_SIZE 0x100000 // 1 Mb
#define HEAP_FLAG_ALLOCATED 1
#define HEAP_FLAG_FREE 0

#define HEAP_METADATA_SIZE 3

typedef struct {
  unsigned char* base;
  unsigned char* end;
} heap_t;

void* heap_alloc(heap_t* hp, size_t sz);

void heap_free(heap_t* hp, void* ptr);

int heap_init(heap_t* target, unsigned int base, unsigned int size);

void heap_dump(heap_t* hp);

size_t heap_buffer_size(void* ptr);


//Kernel Heap
void kernel_heap_init();

void* kernel_heap_alloc(size_t sz);

void kernel_heap_free(void* ptr);

void kernel_heap_dump();

#endif
