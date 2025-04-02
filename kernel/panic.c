#include <sys/panic.h>
#include <system.h>

void
panic (char *message)
{
    asm ("cli");
    printk ("kernel panic: %s", message);
    while (1)
    {
        asm ("cli");
        asm ("hlt");
    }
}