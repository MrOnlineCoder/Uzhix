;	Uzhix Assembler routines

[BITS 32]

extern isr_exception

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15


; ---------   Exceptions  --------

%macro ISR_EX 1
	isr%1:
		pusha
		push gs
		push fs
		push ds
		push es
	    push %1
	    call isr_exception
	    pop es
		pop ds
		pop fs
		pop gs
		popa
		iret
%endmacro

; ---------   IRQ  --------
%macro IRQH 1
	irq%1:
	    cli
	    push byte 0
	    push byte %1+32
	    jmp irq_routine
%endmacro

;Divide By Zero Exception
ISR_EX 0

;Debug Exception
ISR_EX 1

;Non Maskable Interrrupt Exception
ISR_EX 2

;Breakpoint Exception
ISR_EX 3

;Into Detected Overflow Exception
ISR_EX 4

;Out of Bounds Exception
ISR_EX 5

;Invalid Opcode Exception
ISR_EX 6

;No Coprocessor Exception
ISR_EX 7

;Double Fault Exception
ISR_EX 8

;Coprocessor Segment Overrun Exception
ISR_EX 9

;Bad TSS Exception
ISR_EX 10

;Segment Not Present Exception
ISR_EX 11

;Stack Fault Exception
ISR_EX 12

;General Protection Fault Exception
ISR_EX 13

;Page Fault Exception
ISR_EX 14

;Unknown Interrupt Exception
ISR_EX 15

;Coprocessor Fault Exception
ISR_EX 16

;Alignment Check Exception
ISR_EX 17

;Machine Check Exception
ISR_EX 18

;Reserved
ISR_EX 19

;Reserved
ISR_EX 20

;Reserved
ISR_EX 21

;Reserved
ISR_EX 22

;Reserved
ISR_EX 23

;Reserved
ISR_EX 24

;Reserved
ISR_EX 25

;Reserved
ISR_EX 26

;Reserved
ISR_EX 27

;Reserved
ISR_EX 28

;Reserved
ISR_EX 29

;Reserved
ISR_EX 30

;Reserved
ISR_EX 31

IRQH 0
IRQH 1
IRQH 2
IRQH 3
IRQH 4
IRQH 5
IRQH 6
IRQH 7
IRQH 8
IRQH 9
IRQH 10
IRQH 11
IRQH 12
IRQH 13
IRQH 14
IRQH 15

global gdt_load
extern gp

; --------- Loads the GDT --------
gdt_load:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2
    ret
flush2:
    ret

global idt_load
extern idtp

; --------- Loads the IDT --------
idt_load:
    lidt [idtp]
    ret


; --------- Calls C IRQ handler --------
extern irq_handler

irq_routine:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
