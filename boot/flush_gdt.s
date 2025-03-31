.global flush_gdt
flush_gdt:
    .extern gdtptr
    lgdt (gdtptr)
    movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	jmp $0x08, $flushgdtjmp
flushgdtjmp:
    ret