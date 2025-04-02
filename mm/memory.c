#include "multiboot.h"
#include <sys/console.h>
#include <sys/panic.h>
#include <system.h>
#include <stddef.h>
#include <stdint.h>

int total_memory, available_memory;

/* We could track around 4gb of memory */
unsigned char frame_bitmap[131072];

/* This parses the memory map given by GRUB, and performs other tasks (as well
 * as, checks if we even got one */
void
mem_init (multiboot_info_t *mbd)
{
    total_memory = 0;
    available_memory = 0;
    if (!(mbd->flags >> 6 & 0x1))
    {
        panic ("no memory map");
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
    /* We'll mark all free memory as free in the page bitmap */
    for (int i = 0; i < available_memory / 4096; i++)
    {
        frame_bitmap[i] = 0;
    }
    
    /* Most of the time we'll be dealing with these numbers in bytes though*/
    printk ("%dkb total, %dkb free\n", total_memory / 1024,
        available_memory / 1024);
}

/* Here goes the page frame allocator. For now, the kernel is flat memory model, but we still will use this allocator for some stuff. */

void *alloc_page_frame()
{
    for (int i = 0; i < 131072; i++)
    {
        if (frame_bitmap[i] == 0)
        {
            frame_bitmap[i] = 1;
            return (void *)(i * 4096);
        }
    }
    printk("pfa: not enough memory, returning null\n");
    return NULL;
}

void free_page_frame (void *addr)
{
    uint32_t frame = ((uint32_t)addr) / 4096;
    if (frame < 131072)
    {
        frame_bitmap[frame] = 0;
        return;
    }
    printk("pfa: frame addr not in bitmap range\n");
}