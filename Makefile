#
# Uzhix Makefile
#


OBJ=obj
OUT=build
CFLAGS=-std=c99 -static -O2 -ffreestanding -Iinclude -Wall -Ilibc/include -Lbuild -llibk
LDLIBS=build/libk.a
CC=i686-elf-gcc

BOOTFILES=$(OBJ)/multiboot.o $(OBJ)/boot.o
KERNELFILES= $(OBJ)/kernel.o $(OBJ)/gdt.o $(OBJ)/io.o $(OBJ)/panic.o $(OBJ)/irq.o $(OBJ)/isr.o $(OBJ)/idt.o
DRIVERS=$(OBJ)/screen.o $(OBJ)/pic.o $(OBJ)/cmos.o
MMFILES=$(OBJ)/heap.o $(OBJ)/paging.o $(OBJ)/pmm.o

OBJFILES=$(BOOTFILES) $(KERNELFILES) $(DRIVERS) $(MMFILES)


# === OBJECT FILES ===
multiboot.o:
	nasm -felf32 boot/multiboot.asm -o $(OBJ)/multiboot.o

gdt.o:
	$(CC) -o $(OBJ)/gdt.o -c kernel/gdt.c $(CFLAGS)

boot.o:
	nasm -felf32 boot/boot.asm -o $(OBJ)/boot.o

screen.o:
	$(CC) -o $(OBJ)/screen.o -c drivers/screen.c $(CFLAGS)

kernel.o:
	$(CC) -o $(OBJ)/kernel.o -c kernel/kmain.c $(CFLAGS)

io.o:
	$(CC) -o $(OBJ)/io.o -c kernel/io.c $(CFLAGS)

panic.o:
	$(CC) -o $(OBJ)/panic.o -c kernel/panic.c $(CFLAGS)

irq.o:
	$(CC) -o $(OBJ)/irq.o -c kernel/irq.c $(CFLAGS)

isr.o:
	$(CC) -o $(OBJ)/isr.o -c kernel/isr.c $(CFLAGS)

pic.o:
	$(CC) -o $(OBJ)/pic.o -c drivers/pic.c $(CFLAGS)

idt.o:
	$(CC) -o $(OBJ)/idt.o -c kernel/idt.c $(CFLAGS)

cmos.o:
	$(CC) -o $(OBJ)/cmos.o -c drivers/cmos.c $(CFLAGS)


# == memory manager ==
heap.o:
	$(CC) -o $(OBJ)/heap.o -c mm/heap.c $(CFLAGS)

paging.o:
	$(CC) -o $(OBJ)/paging.o -c mm/paging.c $(CFLAGS)

pmm.o:
	$(CC) -o $(OBJ)/pmm.o -c mm/pmm.c $(CFLAGS)


# == libc ==
libk:
	(cd libc; make libk)


# === Main target ===
prepare:
	echo mkdir -p obj

link:
	$(CC) -T link.ld -o $(OUT)/uzhix.img -ffreestanding -O2 -nostdlib $(OBJFILES) $(LDLIBS) -lgcc

# === helper targets ===
drivers: screen.o pic.o cmos.o

mm: heap.o paging.o pmm.o

krnl: kernel.o gdt.o io.o panic.o idt.o isr.o irq.o

irq: idt.o isr.o irq.o

asm: multiboot.o boot.o

###################################################################################################
Image: prepare asm krnl mm drivers link
###################################################################################################

# === ISO ===

iso:
	cp $(OUT)/uzhix.img build/isodir/boot/uzhix.bin
	grub-mkrescue -o build/uzhix.iso build/isodir

clean:
	rm -f $(OBJ)/*.o
	rm -f $(OUT)/uzhix.img
