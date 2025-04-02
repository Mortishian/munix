#include <stdint.h>
#include <sys/console.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/tty.h>
#include <system.h>

#include "multiboot.h"

tty tty0;

extern void trap_init ();
extern void setup_gdt ();
extern void sti ();

void
main (multiboot_info_t *mbd, unsigned int magic)
{
    setup_gdt ();
    tty_init (&tty0);
    printk("Starting munix...\n");
    trap_init ();
    mem_init (mbd);
    printk ("OK\n\r");
    /* This is the safest place to enable interrupts */
    sti ();
    for (;;)
        ;
}