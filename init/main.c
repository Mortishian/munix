#include <stdint.h>
#include <sys/console.h>
#include <sys/timer.h>
#include <sys/tty.h>
#include <sys/memory.h>
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
    trap_init ();
    mem_init (mbd);
    printk ("OK\n\r");
    tty_clear_buffer (&tty0);
    /* This is the safest place to enable interrupts */
    sti ();
    for (;;)
        ;
}