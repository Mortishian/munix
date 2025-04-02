#include "multiboot.h"
#include <sys/console.h>
#include <sys/panic.h>
#include <system.h>

int total_memory, available_memory;

/* This parses the memory map given by GRUB, and performs other tasks (as well
 * as, checks if we even got one */
void
mem_init (multiboot_info_t *mbd)
{
    total_memory = 0;
    available_memory = 0;
    if (!(mbd->flags >> 6 & 0x1))
    {
        panic ("invalid memory map");
    }

    for (int i = 0; i < mbd->mmap_length; i += sizeof (multiboot_memory_map_t))
    {
        multiboot_memory_map_t *mmmt
            = (multiboot_memory_map_t *)(mbd->mmap_addr + i);

        total_memory = total_memory + mmmt->len;

        if (mmmt->type == MULTIBOOT_MEMORY_AVAILABLE)
        {
            available_memory = available_memory + mmmt->len;
        }
    }
    /* Most of the time we'll be dealing with these numbers in bytes though*/
    printk ("%dkb total, %dkb free\n", total_memory / 1024,
        available_memory / 1024);
}