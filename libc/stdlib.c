/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <stdlib.h>

#ifdef _uzhix_libk
  #include <uzhix/heap.h>
#else

#endif

void *malloc(size_t size) {
#ifdef _uzhix_libk
  return kernel_heap_alloc(size);
#else
  //TODO: add userspace malloc
#endif
}

void free(void *ptr) {
#ifdef _uzhix_libk
  return kernel_heap_free(ptr);
#else
  //TODO: add userspace free
#endif
}
