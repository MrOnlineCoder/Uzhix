/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H

typedef unsigned long size_t;

void* memcpy(void* dest, const void* src, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);
void* memset(void* dest, int v, size_t n);
int strcmp(const char* s1, const char* s2);
size_t strlen(const char* str);
char* strcpy(char* to, const char* from);
void itoa(char *buf, unsigned long int n, int base);

#endif
