/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/mm/paging.h>
#include <uzhix/io.h>

#include <stdio.h>

page_directory_t* current_pagedir;
physaddr_t _current_pagedir_addr;

page_directory_t kernel_page_directory __attribute__ ((aligned (PAGE_SIZE)));

page_table_t kernel_identity_table __attribute__ ((aligned (PAGE_SIZE)));

void paging_setentry(uintptr_t* ptr, physaddr_t addr, uint32_t flags) {
  *ptr = 0x0;
  *ptr = addr | flags;
}

void paging_enable() {
  _current_pagedir_addr = (physaddr_t) kernel_page_directory.entries;

  asmv("mov %0, %%cr3":: "r"(_current_pagedir_addr));

  uint32_t cr0;
  asmv("mov %%cr0, %0": "=r"(cr0));
  cr0 |= 0x80000000; // Enable paging!

  asmv("mov %0, %%cr0":: "r"(cr0));
}

void vm_identity_map_kernel() {
  current_pagedir = &kernel_page_directory;

  //mark all page directory entires as not-present for now
  for (unsigned int i = 0; i < 1024; i++) {
    paging_setentry(&kernel_page_directory.entries[i], 0x0, 0x0);
  }

  //setup page table for 1st 4MB
  for (unsigned int i = 0; i < 1024; i++) {
    paging_setentry(&kernel_identity_table.pages[i], (physaddr_t) i * PAGE_SIZE, PTE_FLAG_PRESENT | PTE_FLAG_WRITEABLE);
  }

  //tell page directory about it's first table
  paging_setentry(&kernel_page_directory.entries[0], (physaddr_t) kernel_identity_table.pages, PDE_FLAG_PRESENT | PDE_FLAG_WRITEABLE);
}

void vm_map_page(virtaddr_t virt, physaddr_t phys) {
  uint32_t pd_index = PAGE_DIRECTORY_INDEX(virt);
  uint32_t pt_index = PAGE_TABLE_INDEX(virt);

  
}
