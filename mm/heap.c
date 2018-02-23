/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/heap.h>
#include <uzhix/io.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
  Heap structure
  -----------------------------------------------------
  01 32 **32 bytes of data** | free memory
  -----------------------------------------------------
  01 - means ALLOCTED
  32 - size of the block
*/

void* heap_alloc(heap_t* hp, size_t size) {
  unsigned char* ptr = hp->base;


  while (ptr < hp->end) {
    //search for the block

    //we found free block
    if (ptr[0] == HEAP_FLAG_FREE) {
      //check it's size
      unsigned char bsz = ptr[1];

      //if it perfectly fits our block - flag and return
      if (bsz == size || bsz == 0) {
        ptr[0] = HEAP_FLAG_ALLOCATED;
        ptr[1] = size;

        return ptr + 2;
      }

      //block is not large enough, skip it
      //accept if this block wasn't touched
      if (bsz < size) {
        ptr += bsz + 2; //+2 is 2 bytes: allocated/free block marker and size of the block
        continue;
      }

      //the situation where we need to divide one block into 2
      if (size < bsz) {

        //nevertheless, if second block is smaller than 3 bytes (can only fit metadata) - then give more memory
        if (bsz - size < 3) {
          ptr[0] = HEAP_FLAG_ALLOCATED;
          ptr[1] = bsz;

          return ptr + 2;
        }


        //divide blocks
        ptr[0] = HEAP_FLAG_ALLOCATED;
        ptr[1] = size;

        ptr[2 + size] = HEAP_FLAG_FREE;
        ptr[2 + size + 1] = bsz - size;

        return ptr + 2;
      }
    } else if (ptr[0] == HEAP_FLAG_ALLOCATED) {
      ptr += ptr[1] + 2;
      continue;
    }
  }

  return NULL;
}

void heap_free(heap_t* hp, void* ptr) {
  unsigned char* p = (unsigned char* ) ptr;

  if (p > hp->end) return;

  //find block marker
  if (p[-2] == HEAP_FLAG_ALLOCATED) {
    p[-2] = HEAP_FLAG_FREE;
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
      printf("block %d: allocated, start=%p size=%d\n", block, ptr, ptr[1]);
      block++;
      ptr += ptr[1] + 2;
    } else {
      if (ptr[0] == HEAP_FLAG_FREE) {
        printf("block %d: free, start=%p, size=%d\n", block, ptr, ptr[1]);
        if (ptr[1] == 0) {
          printf("* end block *\n");
          break;
          return;
        }
        block++;
        ptr += ptr[1] + 2;
      }
    }
  }
}
