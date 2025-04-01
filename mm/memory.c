#include "multiboot.h"
#include <system.h>
#include <sys/console.h>

int *lower_memory, *upper_memory, *total_memory;

void mem_init(multiboot_info_t *mbd)
{
    lower_memory = (int*)mbd->mem_lower;
    upper_memory = (int*)mbd->mem_upper;
    //total_memory = mbd->mem_upper + mbd->mem_lower;
    printk("lower memory %dkb, upper memory %dkb\n", lower_memory, upper_memory);
}