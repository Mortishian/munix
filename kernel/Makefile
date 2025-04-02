# Makefile for the actual kernel
CC=i386-elf-gcc 
AS=i386-elf-as
LD=i386-elf-ld 
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ../include/

OBJS=console.o printk.o tty.o traps.o stub.o ports.o timer.o keyboard.o panic.o

all: $(OBJS)
	$(LD) -r -o ../build/kernel.o $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) -c $< -o $@