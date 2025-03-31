#include <stdint.h>
#include <sys/console.h>
#include <sys/timer.h>
#include <sys/tty.h>
#include <system.h>

tty tty0;

extern void trap_init ();
extern void sti ();

void
main ()
{
    tty_init (&tty0);
    trap_init ();
    printk ("OK\n\r");
    tty_clear_buffer(&tty0);
    /* This is the safest place to enable interrupts */
    sti ();
    for (;;) ;
}