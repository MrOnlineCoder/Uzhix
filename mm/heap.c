/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/mm/heap.h>
#include <uzhix/io.h>
#include <uzhix/uzhix.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <limits.h>

heap_t kernel_heap;

/*
  Heap structure
  -----------------------------------------------------
  FL SZ16 **SZ bytes of data** | free memory
  -----------------------------------------------------
  FL - is block free or not? (uint_8)
  SZ16 - size of the block (uint_16 or 2 bytes)
*/

void* heap_alloc(heap_t* hp, size_t sz) {
  unsigned char* ptr = hp->base;
  uint16_t size = (uint16_t) sz;

  if (size > USHRT_MAX || size < 1) {
    return NULL;
  }

  while (ptr < hp->end) {
    //search for the block

    //we found free block
    if (ptr[0] == HEAP_FLAG_FREE) {
      //check it's size
      uint16_t bsz = MAKE_WORD(ptr[1], ptr[2]);

      //if it perfectly fits our block - flag and return
      if (bsz == size || bsz == 0) {
        ptr[0] = HEAP_FLAG_ALLOCATED;
        ptr[1] = WORD_HIGH(size);
        ptr[2] = WORD_LOW(size);

        return ptr + HEAP_METADATA_SIZE;
      }

      //block is not large enough, skip it
      //accept if this block wasn't touched
      if (bsz < size) {
        ptr += bsz + HEAP_METADATA_SIZE; //+3 is 3 bytes: allocated/free block marker and size of the block
        continue;
      }

      //the situation where we need to divide one block into 2
      if (size < bsz) {

        //nevertheless, if second block is smaller than 3 bytes (can only fit metadata) - then give more memory
        if (bsz - size < 3) {
          ptr[0] = HEAP_FLAG_ALLOCATED;
          ptr[1] = WORD_HIGH(bsz);
          ptr[2] = WORD_LOW(bsz);

          return ptr + HEAP_METADATA_SIZE;
        }


        //divide blocks
        ptr[0] = HEAP_FLAG_ALLOCATED;
        ptr[1] = WORD_HIGH(size);
        ptr[2] = WORD_LOW(size);

        ptr[2 + size] = HEAP_FLAG_FREE;
        ptr[2 + size + 1] = WORD_HIGH((bsz - size));
        ptr[2 + size + 2] = WORD_LOW((bsz - size));

        return ptr + HEAP_METADATA_SIZE;
      }
    } else if (ptr[0] == HEAP_FLAG_ALLOCATED) {
      ptr += MAKE_WORD(ptr[1], ptr[2]) + HEAP_METADATA_SIZE;
      continue;
    } else {
      heap_dump(hp);
      panic("heap flag byte corrupted");
    }
  }

  return NULL;
}

size_t heap_buffer_size(void* ptr) {
  unsigned char* p = (unsigned char* ) (ptr-HEAP_METADATA_SIZE);

  uint16_t size = MAKE_WORD(p[1], p[2]);

  return size;
}

void heap_free(heap_t* hp, void* ptr) {
  unsigned char* p = (unsigned char* ) ptr;

  if (p > hp->end) return;

  //find block marker
  if (p[-HEAP_METADATA_SIZE] == HEAP_FLAG_ALLOCATED) {
    p[-HEAP_METADATA_SIZE] = HEAP_FLAG_FREE;
    //memset(p, 0, p[-1]);
  }
}

int heap_init(heap_t* target, unsigned int base, unsigned int size) {
  target->base = (unsigned char*) base;
  target->end = (unsigned char*) (base + size);

  memset(target->base, 0, size);

  return 0;
}

void heap_dump(heap_t* hp) {
  unsigned char* ptr = hp->base;

  int block = 0;

  printf("\nHeap at base %p dump:\n", hp->base);

  while (ptr < hp->end) {
    if (ptr[0] == HEAP_FLAG_ALLOCATED) {
      printf("block %d: allocated, start=%p size=%d\n", block, ptr, MAKE_WORD(ptr[1], ptr[2]));
      block++;
      ptr += MAKE_WORD(ptr[1], ptr[2]) + HEAP_METADATA_SIZE;
    } else {
      if (ptr[0] == HEAP_FLAG_FREE) {
        printf("block %d: free, start=%p, size=%d\n", block, ptr, MAKE_WORD(ptr[1], ptr[2]));
        if (MAKE_WORD(ptr[1], ptr[2]) == 0) {
          printf("* end block *\n");
          return;
        }
        block++;
        ptr += MAKE_WORD(ptr[1], ptr[2]) + HEAP_METADATA_SIZE;
      }
    }
  }
}

/*
===================
  Kernel heap
===================
*/

void kernel_heap_init() {
  heap_init(&kernel_heap, KERNEL_HEAP_START, KERNEL_HEAP_SIZE);
}

void* kernel_heap_alloc(size_t sz) {
  return heap_alloc(&kernel_heap, sz);
}

void kernel_heap_free(void* ptr) {
  heap_free(&kernel_heap, ptr);
}

void kernel_heap_dump() {
  heap_dump(&kernel_heap);
}
