# This builds all the subdirectories, and creates a real .bin and .iso file, most of these subdirectories
# build relocatable images by default.

TARGET=build/image.bin
ISOTARGET=build/image.iso
CC=i386-elf-gcc

all: build
	$(MAKE) -C boot
	$(MAKE) -C include
	$(MAKE) -C init
	$(MAKE) -C kernel
	$(MAKE) -C mm
	$(CC) -T linker.ld -o build/image.bin -ffreestanding -O2 -nostdlib build/*.o -lgcc
	cp $(TARGET) sysroot/boot/image.bin
	grub2-mkrescue -o $(ISOTARGET) sysroot
	sync
	qemu-system-i386 -cdrom build/image.iso -m 16

clean:
	rm boot/*.o init/*.o kernel/*.o mm/*.o
	rm build/*
	rm sysroot/boot/image.bin

format:
	@find boot include init kernel mm -type f \( -name "*.c" -o -name "*.h" \) | xargs clang-format -i

build:
	mkdir build