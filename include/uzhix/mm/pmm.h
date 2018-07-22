/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

/*
  Physical Memory Manager

  Divides all avaliable memory into PAGE_SIZEd chunks (4KB usually).
  Keeps track of used/unused chunks via a bitmap.
*/

#ifndef _PMM_H
#define _PMM_H

#include "paging.h"

#define PMM_BLOCK_SIZE PAGE_SIZE

#define BM_BITS_PER_ITEM 32
#define BM_ARRAY_OFFSET(b) ((b) / BM_BITS_PER_ITEM)
#define BM_BIT_OFFSET(b)  ((b) % BM_BITS_PER_ITEM)

void* pmm_allocate_block();
void pmm_free_block(void* ptr);
void pmm_init(uint32_t memsize);

#endif
