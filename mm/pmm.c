/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/mm/pmm.h>
#include <stdlib.h>
#include <string.h>
#include <uzhix/uzhix.h>

uint32_t* pmm_bitmap;
uint32_t _totalBlocks;

static int pmm_check_bit(size_t idx) {
  uint32_t item = pmm_bitmap[BM_ARRAY_OFFSET(idx)];
  uint32_t bit = item & (1 << BM_BIT_OFFSET(idx));

  return bit != 0;
}

static void pmm_set_bit(size_t idx) {
  pmm_bitmap[BM_ARRAY_OFFSET(idx)] |= (1 << BM_BIT_OFFSET(idx));
}

static void pmm_clear_bit(size_t idx) {
  pmm_bitmap[BM_ARRAY_OFFSET(idx)] &= ~(1 << BM_BIT_OFFSET(idx));
}

void* pmm_allocate_block() {
  for (size_t i = 0; i < _totalBlocks; i++) {
    if (pmm_bitmap[BM_ARRAY_OFFSET(i)] == 0xFFFFFFFF) {
      i += BM_BITS_PER_ITEM;
      continue;
    }

    if (pmm_check_bit(i) == 0) {
      pmm_set_bit(i);
      return (void*) (i * PMM_BLOCK_SIZE);
    }
  }

  panic("out of physical memory.");
  return NULL;
}

void pmm_free_block(void* ptr) {
  size_t idx = (physaddr_t) ptr / PMM_BLOCK_SIZE;

  pmm_clear_bit(idx);
}

void pmm_init(uint32_t memsize) {
  _totalBlocks = memsize / PAGE_SIZE;
  pmm_bitmap = malloc(_totalBlocks * sizeof(uint32_t));

  memset(pmm_bitmap, 0, _totalBlocks * sizeof(uint32_t));

  //first 4MB are always used by the kernel
  for (size_t i = 0; i < 32; i++) {
    pmm_bitmap[i] = 0xFFFFFFFF;
  }
}
