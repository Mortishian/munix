#ifndef SYSTEM_H
#define SYSTEM_H
void printk (const char *fmt, ...);
unsigned char inb (unsigned short _port);
void outb (unsigned short _port, unsigned char _data);
#endif