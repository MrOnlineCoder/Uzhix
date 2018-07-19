/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>

#define PDE_FLAG_PRESENT 0x1
#define PDE_FLAG_WRITEABLE 0x2
#define PDE_FLAG_USER 0x4
#define PDE_FLAG_WRITETHROUGH 0x8
#define PDE_FLAG_CACHEOFF 0x10
#define PDE_FLAG_ACCESSED 0x20
#define PDE_FLAG_4MB 0x80
#define PDE_ADDRESS_MASK 0xFFFFF000

#define PTE_FLAG_PRESENT 0x1
#define PTE_FLAG_WRITEABLE 0x2
#define PTE_FLAG_USER 0x4
#define PTE_FLAG_WRITETHROUGH 0x8
#define PTE_FLAG_CACHEOFF 0x10
#define PTE_FLAG_ACCESSED 0x20
#define PTE_FLAG_DIRTY 0x40
#define PTE_FLAG_GLOBAL 0x100
#define PTE_ADDRESS_MASK 0xFFFFF000

#define PAGE_SIZE 0x1000 //4 KB

#define PAGE_DIRECTORY_INDEX(x) ((virtaddr_t) x) >> 22;
#define PAGE_TABLE_INDEX(x) (((virtaddr_t) x) >> 12) & 0x03FF;

typedef uintptr_t physaddr_t;
typedef uintptr_t virtaddr_t;

typedef uint32_t pte_t;
typedef uint32_t pde_t;

typedef struct {
  pte_t pages[1024];
} page_table_t;

typedef struct {
  pde_t entries[1024];
} page_directory_t;

void paging_setentry(uintptr_t* ptr, physaddr_t addr, uint32_t flags);

extern void paging_load();
void paging_enable();

void paging_map(virtaddr_t virt, physaddr_t phys);

void paging_identity_map_kernel();

void paging_test();

#endif
