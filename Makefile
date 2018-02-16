#
# Uzhix Makefile
#


OBJ=obj
OUT=build
CFLAGS=-std=c99 -static -O2 -ffreestanding -Iinclude -Wall -Ilibc/include -Lbuild -llibk
LDLIBS=build/libk.a

BOOTFILES=$(OBJ)/multiboot.o $(OBJ)/boot.o
KERNELFILES= $(OBJ)/kernel.o $(OBJ)/gdt.o
DRIVERS=$(OBJ)/screen.o
LIBFILES=$(OBJ)/string.o $(OBJ)/stdio.o

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

# == libc ==
libk:
	(cd libc; make libk)

# === Main target ===
prepare:
	echo mkdir -p obj

link:
	ld -m elf_i386 -o $(OUT)/uzhix.img -T link.ld $(OBJFILES) $(LDLIBS)

Image: prepare multiboot.o boot.o kernel.o gdt.o screen.o link

clean:
	rm -f $(OBJ)/*.o
	rm -f $(OUT)/uzhix.img

# === ISO ===

iso:
	cp $(OUT)/uzhix.img build/isodir/boot/uzhix.bin
	grub-mkrescue -o build/uzhix.iso build/isodir
