# Uzhix C Standard Library Makefile

CC=gcc
AR=ar
KFLAGS=-ffreestanding -Wall -Wextra -D_uzhix_libk -std=c99 -Iinclude -I../include/ -o obj/$@

stdio.o:
	$(CC) $(KFLAGS) -c stdio.c

string.o:
	$(CC) $(KFLAGS) -c string.c

libk: stdio.o string.o
	$(AR) rcsv ../build/libk.a obj/stdio.o obj/string.o

libc:
	echo Error: No libc avaliable to build right now!
