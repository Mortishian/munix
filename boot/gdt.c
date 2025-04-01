#include <stdint.h>

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) Gdtptr;

typedef struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_mid;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute__((packed)) GDTentry;

GDTentry gdt[5];

void setGDTEntry(int num, uint32_t base, uint32_t limit, uint8_t access,
                 uint8_t granularity) {
  gdt[num].base_low = base & 0xFFFF;
  gdt[num].base_mid = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;
  gdt[num].limit_low = limit & 0xFFFF;
  gdt[num].granularity = (limit >> 16) & 0x0F;
  gdt[num].granularity |= (granularity & 0xF0);
  gdt[num].access = access;
}

Gdtptr gdtptr;

extern void flush_gdt();

void setup_gdt() {
  setGDTEntry(0, 0, 0, 0, 0);
  setGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  setGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  setGDTEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  setGDTEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

  gdtptr.limit = sizeof(gdt) - 1;
  gdtptr.base = (uint32_t)&gdt;
  flush_gdt();
}