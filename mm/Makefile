# Makefile for mm
CC=i386-elf-gcc 
AS=i386-elf-as
LD=i386-elf-ld 
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ../include/

OBJS=memory.o

all: $(OBJS)
	$(LD) -r -o ../build/mm.o $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) -c $< -o $@