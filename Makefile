#
# Uzhix Makefile
#


OBJ=obj
OUT=build
CFLAGS=-std=c99 -static -O2 -ffreestanding -Iinclude -Wall -Ilibc/include -Lbuild -llibk
LDLIBS=build/libk.a

BOOTFILES=$(OBJ)/multiboot.o $(OBJ)/boot.o
KERNELFILES= $(OBJ)/kernel.o $(OBJ)/gdt.o $(OBJ)/io.o $(OBJ)/panic.o $(OBJ)/irq.o $(OBJ)/isr.o $(OBJ)/idt.o
DRIVERS=$(OBJ)/screen.o $(OBJ)/pic.o $(OBJ)/cmos.o

OBJFILES=$(BOOTFILES) $(KERNELFILES) $(DRIVERS)


# === OBJECT FILES ===
multiboot.o:
	nasm -felf32 boot/multiboot.asm -o $(OBJ)/multiboot.o

gdt.o:
	gcc -o $(OBJ)/gdt.o -c kernel/gdt.c $(CFLAGS)

boot.o:
	nasm -felf32 boot/boot.asm -o $(OBJ)/boot.o

screen.o:
	gcc -o $(OBJ)/screen.o -c drivers/screen.c $(CFLAGS)

kernel.o:
	gcc -o $(OBJ)/kernel.o -c kernel/kmain.c $(CFLAGS)

io.o:
		gcc -o $(OBJ)/io.o -c kernel/io.c $(CFLAGS)

panic.o:
		gcc -o $(OBJ)/panic.o -c kernel/panic.c $(CFLAGS)

irq.o:
		gcc -o $(OBJ)/irq.o -c kernel/irq.c $(CFLAGS)

isr.o:
		gcc -o $(OBJ)/isr.o -c kernel/isr.c $(CFLAGS)

pic.o:
		gcc -o $(OBJ)/pic.o -c drivers/pic.c $(CFLAGS)

idt.o:
		gcc -o $(OBJ)/idt.o -c kernel/idt.c $(CFLAGS)

cmos.o:
		gcc -o $(OBJ)/cmos.o -c drivers/cmos.c $(CFLAGS)

# == libc ==
libk:
	(cd libc; make libk)


# === Main target ===
prepare:
	echo mkdir -p obj

link:
	ld -m elf_i386 -o $(OUT)/uzhix.img -T link.ld $(OBJFILES) $(LDLIBS)

# === helper targets ===
drivers: screen.o pic.o cmos.o

krnl: kernel.o gdt.o io.o panic.o idt.o isr.o irq.o

irq: idt.o isr.o irq.o

asm: multiboot.o boot.o

###################################################################################################
Image: prepare asm krnl drivers link
###################################################################################################

# === ISO ===

iso:
	cp $(OUT)/uzhix.img build/isodir/boot/uzhix.bin
	grub-mkrescue -o build/uzhix.iso build/isodir

clean:
	rm -f $(OBJ)/*.o
	rm -f $(OUT)/uzhix.img
