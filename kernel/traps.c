/* this is the file with IDT functions and exception handlers. For now, they
 * will only help in debugging. Like a proper operating system, we define
 * assembly stubs for these in stub.s that will call the actual handlers
 */
#include <stdint.h>
#include <system.h>

void
infinite_loop ()
{
    unsigned int cr2;
    asm ("mov %%cr2, %0" : "=r"(cr2));
    printk ("at addr %x", cr2);
    while (1)
    {
        asm ("cli");
        asm ("hlt");
    }
}

void
isr0 ()
{
    printk ("Division by zero exception\n");
    infinite_loop ();
}

void
isr1 ()
{
    printk ("Debug exception\n");
    infinite_loop ();
}

void
isr2 ()
{
    printk ("Non Maskable Interrupt Exception\n");
    infinite_loop ();
}

void
isr3 ()
{
    printk ("Breakpoint Exception\n");
    infinite_loop ();
}

void
isr4 ()
{
    printk ("Into Detected Overflow Exception\n");
    infinite_loop ();
}

void
isr5 ()
{
    printk ("Out of Bounds Exception\n");
    infinite_loop ();
}

void
isr6 ()
{
    printk ("Invalid Opcode Exception\n");
    infinite_loop ();
}

void
isr7 ()
{
    printk ("No Coprocessor Exception\n");
    infinite_loop ();
}

void
isr8 ()
{
    printk ("Double Fault Exception\n");
    infinite_loop ();
}

void
isr9 ()
{
    printk ("Coprocessor Segment Overrun Exception\n");
    infinite_loop ();
}

void
isr10 ()
{
    printk ("Bad TSS Exception\n");
    infinite_loop ();
}

void
isr11 ()
{
    printk ("Segment Not Present Exception\n");
    infinite_loop ();
}

void
isr12 ()
{
    printk ("Stack Fault Exception\n");
    infinite_loop ();
}

void
isr13 ()
{
    printk ("General Protection Fault Exception\n");
    infinite_loop ();
}

void
isr14 ()
{
    printk ("Page Fault Exception\n");
    infinite_loop ();
}

void
isr15 ()
{
    printk ("Unknown Interrupt Exception\n");
    infinite_loop ();
}

void
isr16 ()
{
    printk ("Coprocessor Fault Exception");
    infinite_loop ();
}

void
isr17 ()
{
    printk ("Alignment Check Exception");
    infinite_loop ();
}

void
isr18 ()
{
    printk ("Machine Check Exception");
    infinite_loop ();
}

void
isr_reserved ()
{
    printk ("Reserved (19-31) Exception\n");
    infinite_loop ();
}

struct idt_entry
{
    unsigned short base_low;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_high;
} __attribute__ ((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__ ((packed));

struct idt_entry idt[256];
struct idt_ptr idtptr;

void
set_trap_gate (int num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_low = base & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].base_high = (base >> 16) & 0xFFFF;
}

extern void do_isr0 ();
extern void do_isr1 ();
extern void do_isr2 ();
extern void do_isr3 ();
extern void do_isr4 ();
extern void do_isr5 ();
extern void do_isr6 ();
extern void do_isr7 ();
extern void do_isr8 ();
extern void do_isr9 ();
extern void do_isr10 ();
extern void do_isr11 ();
extern void do_isr12 ();
extern void do_isr13 ();
extern void do_isr14 ();
extern void do_isr15 ();
extern void do_isr16 ();
extern void do_isr17 ();
extern void do_isr18 ();
extern void do_isr_reserved ();

extern void do_irq0 ();
extern void do_irq1 ();

extern void load_idt ();

void
trap_init ()
{
    outb (0x20, 0x11);
    outb (0xA0, 0x11);
    outb (0x21, 0x20);
    outb (0xA1, 0x28);
    outb (0x21, 0x04);
    outb (0xA1, 0x02);
    outb (0x21, 0x01);
    outb (0xA1, 0x01);
    outb (0x21, 0x0);
    outb (0xA1, 0x0);
    set_trap_gate (0, (unsigned)do_isr0, 0x08, 0x8E);
    set_trap_gate (1, (unsigned)do_isr1, 0x08, 0x8E);
    set_trap_gate (2, (unsigned)do_isr2, 0x08, 0x8E);
    set_trap_gate (3, (unsigned)do_isr3, 0x08, 0x8E);
    set_trap_gate (4, (unsigned)do_isr4, 0x08, 0x8E);
    set_trap_gate (5, (unsigned)do_isr5, 0x08, 0x8E);
    set_trap_gate (6, (unsigned)do_isr6, 0x08, 0x8E);
    set_trap_gate (7, (unsigned)do_isr7, 0x08, 0x8E);
    set_trap_gate (8, (unsigned)do_isr8, 0x08, 0x8E);
    set_trap_gate (9, (unsigned)do_isr9, 0x08, 0x8E);
    set_trap_gate (10, (unsigned)do_isr10, 0x08, 0x8E);
    set_trap_gate (11, (unsigned)do_isr11, 0x08, 0x8E);
    set_trap_gate (12, (unsigned)do_isr12, 0x08, 0x8E);
    set_trap_gate (13, (unsigned)do_isr13, 0x08, 0x8E);
    set_trap_gate (14, (unsigned)do_isr14, 0x08, 0x8E);
    set_trap_gate (15, (unsigned)do_isr15, 0x08, 0x8E);
    set_trap_gate (16, (unsigned)do_isr16, 0x08, 0x8E);
    set_trap_gate (17, (unsigned)do_isr17, 0x08, 0x8E);
    set_trap_gate (18, (unsigned)do_isr18, 0x08, 0x8E);
    set_trap_gate (32, (unsigned)do_irq0, 0x08, 0x8E);
    set_trap_gate (33, (unsigned)do_irq1, 0x08, 0x8E);
    for (int i = 19; i < 31; i++)
    {
        set_trap_gate (i, (unsigned)do_isr_reserved, 0x08, 0x8E);
    }
    idtptr.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtptr.base = (uint32_t)&idt;
    load_idt ();
}