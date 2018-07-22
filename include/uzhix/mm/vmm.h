/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _VMM_H
#define _VMM_H

#include <uzhix/mm/paging.h>

#define VMM_BOOT_CODE_SIZE 0x100000
#define VMM_KERNEL_CODE_SIZE 0x200000
#define VMM_KERNEL_HEAP_SIZE 0x100000

#define VMM_TOTAL_MEM 0x1000000

#define VMM_ALLOCATION_START VMM_BOOT_CODE_SIZE+VMM_KERNEL_CODE_SIZE+VMM_KERNEL_HEAP_SIZE+PAGE_SIZE

physaddr_t vmm_get_free_page();

void vmm_free_page();

#endif
