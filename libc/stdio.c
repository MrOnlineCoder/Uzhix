/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

/*
  Version-dependent includes
*/
#ifdef _uzhix_libk
#include <uzhix/drivers/screen.h>
#else
  //TODO: add userspace includes
#endif


/*
  Version-dependent implemenation
*/

char putchar(char c) {

#ifdef _uzhix_libk
  screen_putchar(c);
#else
  //TODO: add userspace putchar
#endif

  return c;
}


int is_format_letter(char c) {
    return c == 'c' ||  c == 'd' || c == 'i' ||c == 'e' ||c == 'E' ||c == 'f' ||c == 'g' ||c == 'G' ||c == 'o' ||c == 's' || c == 'u' || c == 'x' || c == 'X' || c == 'p' || c == 'n';
}

void vsprintf_helper(char * str, const char * format, unsigned int* pos, va_list arg) {
    char c;
    int sign, ival, sys;
    char buf[512];
    unsigned int uval;
    unsigned int size = 8;
    unsigned int i;
    int size_override = 0;
    memset(buf, 0, 512);

    while((c = *format++) != 0) {
        sign = 0;

        if(c == '%') {
            c = *format++;
            switch(c) {
                case 'd':
                case 'u':
                case 'x':
                case 'p':
                    if(c == 'd' || c == 'u')
                        sys = 10;
                    else
                        sys = 16;

                    uval = ival = va_arg(arg, int);
                    if(c == 'd' && ival < 0) {
                        sign= 1;
                        uval = -ival;
                    }
                    itoa(buf, uval, sys);
                    unsigned int len = strlen(buf);
                    // If use did not specify width, then just use len = width
                    if(!size_override) size = len;
                    if((c == 'x' || c == 'p' || c == 'd') && len < size) {
                        for(i = 0; i < len; i++) {
                            buf[size - 1 - i] = buf[len - 1 - i];
                        }
                        for(i = 0; i < size - len; i++) {
                            buf[i] = '0';
                        }
                    }
                    if(c == 'd' && sign) {
                        if(str) {
                            *(str + *pos) = '-';
                            *pos = *pos + 1;
                        }
                        else
                            putchar('-');
                    }
                    if(str) {
                        strcpy(str + *pos, buf);
                        *pos = *pos + strlen(buf);
                    }
                    else {
                        char * t = buf;
                        while(*t) {
                            putchar(*t);
                            t++;
                        }
                    }
                    break;
                case 'c':
                    if(str) {
                        *(str + *pos) = (char)va_arg(arg, int);
                        *pos = *pos + 1;
                    }
                    else {
                        putchar((char)va_arg(arg, int));
                    }
                    break;
                case 's':
                    if(str) {
                        char * t = (char *) va_arg(arg, int);
                        strcpy(str + (*pos), t);
                        *pos = *pos + strlen(t);
                    }
                    else {
                        char * t = (char *) va_arg(arg, int);
                        while(*t) {
                            putchar(*t);
                            t++;
                        }
                    }
                    break;
                default:
                    break;
            }
            continue;
        }
        if(str) {
            *(str + *pos) = c;
            *pos = *pos + 1;
        }
        else {
            putchar(c);
        }

    }
}


void vsprintf(char * str, const char * format, va_list arg) {
    unsigned int pos = 0;
    vsprintf_helper(str, format, &pos, arg);
}


void printf(const char* restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    vsprintf(NULL, format, ap);
    va_end(ap);
}
