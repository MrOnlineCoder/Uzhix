# Uzhix C Standard Library Makefile

CC=i686-elf-gcc
AR=i686-elf-ar
KFLAGS=-ffreestanding -Wall -Wextra -D_uzhix_libk -std=c99 -Iinclude -I../include/ -o obj/$@

stdio.o:
	$(CC) $(KFLAGS) -c stdio.c

string.o:
	$(CC) $(KFLAGS) -c string.c

stdlib.o:
	$(CC) $(KFLAGS) -c stdlib.c

libk: stdio.o string.o stdlib.o
	$(AR) rcsv ../build/libk.a obj/stdio.o obj/string.o obj/stdlib.o

libc:
	echo Error: No libc avaliable to build right now!
