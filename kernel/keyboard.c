#include <stdbool.h>
#include <stdint.h>
#include <sys/tty.h>
#include <sys/console.h>
#include <system.h>

unsigned char kbd_buf[80];
int kbd_buf_position;

unsigned char kbdus[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',    /* 9 */
    '9', '0', '-', '=', '\b',                         /* Backspace */
    '\t',                                             /* Tab */
    'q', 'w', 'e', 'r',                               /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     /* Enter key */
    0,                                                /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`', 0,                                     /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',               /* 49 */
    'm', ',', '.', '/', 0,                            /* Right shift */
    '*', 0,                                           /* Alt */
    ' ',                                              /* Space bar */
    0,                                                /* Caps lock */
    0,                                                /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0, 0,                        /* < ... F10 */
    0,                                                /* 69 - Num lock*/
    0,                                                /* Scroll Lock */
    0,                                                /* Home key */
    0,                                                /* Up Arrow */
    0,                                                /* Page Up */
    '-', 0,                                           /* Left Arrow */
    0, 0,                                             /* Right Arrow */
    '+', 0,                                           /* 79 - End key*/
    0,                                                /* Down Arrow */
    0,                                                /* Page Down */
    0,                                                /* Insert Key */
    0,                                                /* Delete Key */
    0, 0, 0, 0,                                       /* F11 Key */
    0,                                                /* F12 Key */
    0, /* All other keys are undefined */
};

bool capslock;
bool shift;

extern int col;

char
kbd_irq_misc_checks (char character)
{
    if ((shift || capslock) == true && character == '1')
    {
        character = '!';
    }
    if ((shift || capslock) == true && character == '2')
    {
        character = '@';
    }
    if ((shift || capslock) == true && character == '3')
    {
        character = '#';
    }
    if ((shift || capslock) == true && character == '4')
    {
        character = '$';
    }
    if ((shift || capslock) == true && character == '5')
    {
        character = '%';
    }
    if ((shift || capslock) == true && character == '6')
    {
        character = '^';
    }
    if ((shift || capslock) == true && character == '7')
    {
        character = '&';
    }
    if ((shift || capslock) == true && character == '8')
    {
        character = '*';
    }
    if ((shift || capslock) == true && character == '9')
    {
        character = '(';
    }
    if ((shift || capslock) == true && character == '0')
    {
        character = ')';
    }
    if ((shift || capslock) == true && character == '-')
    {
        character = '_';
    }
    if ((shift || capslock) == true && character == '=')
    {
        character = '+';
    }
    if ((shift || capslock) == true && character == '[')
    {
        character = '{';
    }
    if ((shift || capslock) == true && character == ']')
    {
        character = '}';
    }
    if ((shift || capslock) == true && character == ';')
    {
        character = ':';
    }
    if ((shift || capslock) == true && character == ',')
    {
        character = '<';
    }
    if ((shift || capslock) == true && character == '.')
    {
        character = '>';
    }
    if ((shift || capslock) == true && character == '/')
    {
        character = '?';
    }
    if ((shift || capslock) == true && character == '`')
    {
        character = '~';
    }
    return character;
}

void
kb_irq ()
{
    uint8_t scancode = inb (0x60);
    if ((scancode & 0x80) == 0)
    {
        if (scancode == 0x3A)
        {
            (capslock) == !(shift || capslock);
        }
        else if (scancode == 0x2A || scancode == 0x36)
        {
            shift = true;
        }
        else if (scancode == 0x1C)
        {
            extern tty tty0;
            cons_write ("\n");
            for (int i = 0; i < 80; i++)
            {
                kbd_buf[i] = '\0';
            }
            kbd_buf_position = 0;
        }
        else if (scancode == 0x0E)
        {
            if (kbd_buf_position == 0)
            {
                kbd_buf[kbd_buf_position] = '\0';
            }
            else
            {
                printk ("\b");
                kbd_buf_position--;
                kbd_buf[kbd_buf_position] = '\0';
            }
        }
        else
        {
            char character = kbdus[scancode];

            if ((shift || capslock) == true && character >= 'a'
                && character <= 'z')
            {
                character = character - 'a' + 'A';
            }
            character = kbd_irq_misc_checks (character);
            kbd_buf[kbd_buf_position] = character;
            kbd_buf_position++;
            kbd_buf[kbd_buf_position] = '\0';
            extern tty tty0;
            tty_handle_key(&tty0, character);
        }
    }
    else
    {
        if (scancode == 0xAA || scancode == 0xB6)
        {
            shift = false;
        }
    }
    outb (0x20, 0x20);
}