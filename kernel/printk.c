#include <stdarg.h>
#include <stddef.h>
#include <sys/timer.h>
#include <sys/console.h>

int
vsnprintf (char *buffer, size_t size, const char *fmt, va_list args)
{
    char *buf = buffer;
    while (*fmt && (buf - buffer) < size - 1)
    {
        if (*fmt != '%')
        {
            *buf++ = *fmt++;
            continue;
        }

        fmt++;
        if (*fmt == 's')
        {
            char *s = va_arg (args, char *);
            while (*s && (buf - buffer) < size - 1)
                *buf++ = *s++;
        }
        else if (*fmt == 'd' || *fmt == 'x')
        {
            int num = va_arg (args, int);
            int base = (*fmt == 'x') ? 16 : 10;
            char tmp[11];
            int i = 0;
            while (num && i < 10)
            {
                tmp[i++] = "0123456789ABCDEF"[num % base];
                num /= base;
            }
            while (i--)
            {
                *buf++ = tmp[i];
            }
        }
        else
        {
            *buf++ = *fmt;
        }
        fmt++;
    }
    *buf = '\0';
    return buf - buffer;
}

void
printk (const char *fmt, ...)
{
    char buffer[256];
    va_list args;
    va_start (args, fmt);
    int ret = vsnprintf (buffer, sizeof (buffer), fmt, args);
    va_end (args);
    cons_write(buffer);
}
