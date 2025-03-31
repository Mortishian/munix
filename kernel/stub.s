# These are the stubs for ISRs and IRQs, they save the registers, and call the appropriate C handlers.
.global do_irq0
.extern timer_irq
do_irq0:
    pusha
    call timer_irq
    popa
    iret
.global do_irq1
.extern kb_irq
do_irq1:
    pusha
    call kb_irq
    popa
    iret
.global do_isr0
.global do_isr1
.global do_isr2
.global do_isr3
.global do_isr4
.global do_isr5
.global do_isr6
.global do_isr7
.global do_isr8
.global do_isr9
.global do_isr10
.global do_isr11
.global do_isr12
.global do_isr13
.global do_isr14
.global do_isr15
.global do_isr16
.global do_isr17
.global do_isr18
.global do_isr_reserved
.global do_irq0
.extern isr0
.extern isr1
.extern isr2
.extern isr3
.extern isr4
.extern isr5
.extern isr6
.extern isr7
.extern isr8
.extern isr9
.extern isr10
.extern isr11
.extern isr13
.extern isr14
.extern isr15
.extern isr16
.extern isr17
.extern isr18
.extern isr_reserved

.extern timer_irq

do_isr0:
    pusha
    cld
    call isr0
    popa
    iret
do_isr1:
    pusha
    cld
    call isr1
    popa
    iret
do_isr2:
    pusha
    cld
    call isr2
    popa
    iret
do_isr3:
    pusha
    cld
    call isr3
    popa
    iret
do_isr4:
    pusha
    cld
    call isr4
    popa
    iret
do_isr5:
    pusha
    cld
    call isr5
    popa
    iret
do_isr6:
    pusha
    cld
    call isr6
    popa
    iret
do_isr7:
    pusha
    cld
    call isr7
    popa
    iret
do_isr8:
    pusha
    cld
    call isr8
    popa
    add $4, %esp
    iret
do_isr9:
    pusha
    cld
    call isr9
    popa
    iret
do_isr10:
    pusha
    cld
    call isr10
    popa
    iret
do_isr11:
    pusha
    cld
    call isr11
    popa
    add $4, %esp
    iret
do_isr12:
    pusha
    cld
    call isr12
    popa
    add $4, %esp
    iret
do_isr13:
    pusha
    cld
    call isr13
    popa
    add $4, %esp
    iret
do_isr14:
    pusha
    cld
    call isr14
    popa
    add $4, %esp
    iret
do_isr15:
    pusha
    cld
    call isr15
    popa
    iret
do_isr16:
    pusha
    cld
    call isr16
    popa
    iret
do_isr17:
    pusha
    cld
    call isr17
    popa
    iret
do_isr18:
    pusha
    cld
    call isr18
    popa
    iret
do_isr_reserved:
    pusha
    cld
    call isr_reserved
    popa
    iret