/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/


#include <string.h>

void* memcpy(void* dest, const void* src, size_t n) {
  unsigned char* d = (unsigned char*) dest;
	const unsigned char* s = (const unsigned char*) src;

  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}

int memcmp(const void* s1, const void* s2, size_t n) {
  const unsigned char* a = (const unsigned char*) s1;
	const unsigned char* b = (const unsigned char*) s2;

  for (size_t i = 0; i < n; i++) {
    if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
  }

  return 0;
}

void* memset(char* dest, int v, size_t n) {
  unsigned char* buf = (unsigned char*) dest;
  for (size_t i = 0; i < n; i++)
  	buf[i] = (unsigned char) v;
  return dest;
}

int strcmp(const char* s1, const char* s2) {
  unsigned char c1, c2;
  while ((c1 = *s1++) == (c2 = *s2++)) {
      if (c1 == '\0')
          return 0;
  }
  return c1 - c2;
}

size_t strlen(const char* str) {
  size_t len = 0;
  while (str[len])
    len++;

  return len;
}

char* strcpy(char* to, const char* from) {
  size_t sz = strlen(from);

  for (size_t i = 0; i < sz; i++) {
    to[i] = from[i];
  }

  to[sz] = '\0';

  return to;
}
