#include <stdint.h>
#include <sys/console.h>
#include <system.h>

enum vga_colors
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t
vga_entry_color (enum vga_colors fg, enum vga_colors bg)
{
    return fg | bg << 4;
}

static inline uint16_t
vga_entry (unsigned char uc, uint8_t color)
{
    return (uint16_t)uc | (uint16_t)color << 8;
}

uint16_t *buf = (const uint16_t *)0xB8000;
uint8_t def_color;
#define WIDTH 80
#define HEIGHT 24
int col, row;

void
cons_init ()
{
    col = 0;
    row = 0;
    def_color = vga_entry_color (VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}

void
cons_handle_cursor ()
{
    uint16_t pos = row * WIDTH + col;
    outb (0x3D4, 0x0F);
    outb (0x3D5, (uint8_t)(pos & 0xFF));
    outb (0x3D4, 0x0E);
    outb (0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void
cons_new_line ()
{
    if (row == HEIGHT - 1)
    {
        cons_scrup ();
    }
    else
    {
        row++;
        col = 0;
    }
    cons_handle_cursor ();
}

void
cons_scrup ()
{
    for (uint16_t y = 1; y < HEIGHT; y++)
    {
        for (uint16_t x = 0; x < WIDTH; x++)
        {
            buf[(y - 1) * WIDTH + x] = buf[y * WIDTH + x];
        }
    }

    for (uint16_t x = 0; x < WIDTH; x++)
    {
        buf[(HEIGHT - 1) * WIDTH + x] = vga_entry (' ', def_color);
    }

    row = HEIGHT - 1;
    col = 0;
    cons_handle_cursor ();
}

char
cons_putchar (char c)
{
    if (col >= WIDTH)
    {
        cons_new_line ();
    }
    buf[row * WIDTH + col] = vga_entry (c, def_color);
    if (c != '\n' && c != '\r')
    {
        col++;
    }
    cons_handle_cursor ();
    return c;
}

char *
cons_write (char *string)
{
    while (*string)
    {
        if (*string == '\n')
        {
            cons_new_line ();
            string++;
        }
        else if (*string == '\r')
        {
            col = 0;
            cons_handle_cursor ();
            string++;
        }
        else if (*string == '\b')
        {
            col--;
            cons_handle_cursor ();
            string++;
        }
        else if (col == WIDTH)
        {
            cons_new_line ();
        }
        else if (row == HEIGHT)
        {
            cons_scrup ();
        }
        else
        {
            cons_putchar (*string);
            string++;
        }
        cons_handle_cursor ();
    }
    return string;
}