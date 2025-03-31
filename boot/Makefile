# Makefile for boot
CC=i386-elf-gcc 
AS=i386-elf-as
LD=i386-elf-ld 
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

OBJS=boot.o gdt.o flush_gdt.o

all: $(OBJS)
	$(LD) -r -o ../build/boot.o $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) -c $< -o $@