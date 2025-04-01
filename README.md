# munix
This is my 32-bit, i386 kernel. 
# Building
Type in "make" to build everything, and make clean to clean up the object files, .bins and .isos. You should have:
1. grub2-mkrescue, my linux distro doesn't have grub-mkrescue, so if you only have grub-mkrescue instead feel free to change that
2. an i386-elf gcc cross compiler, you can also use i686-elf, but change the variables in all Makefiles
3. qemu-system-i386, for testing.
