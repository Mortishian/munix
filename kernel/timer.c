#include <system.h>
#include <stdint.h>

volatile int tick = 0;

void timer_irq()
{
    tick++;
    outb(0x20, 0x20);
}

void print_ticks(void)
{
    printk("%d", tick);
}