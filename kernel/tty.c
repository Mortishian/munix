/* tty.c implements a simple tty-like interface. There is a buffer, you can read
 * from it and input to it. It can also handle keyboard input. Raw and cooked
 * modes are TODO. For now, there is only one tty (tty0) initialised at boot
 * that printk depends on */
#include <stddef.h>
#include <sys/console.h>
#include <sys/tty.h>

void tty_init(tty *tty) {
  cons_init();
  tty->input_head = 0;
  tty->input_tail = 0;
  for (int i = 0; i < 1024; i++) {
    tty->input_buffer[i] = 0;
  }
}

int tty_write(tty *tty, char *buf, int length) {
  for (size_t i = 0; i < length; i++) {
    int next_head = (tty->input_head + 1) % 1024;
    if (next_head == tty->input_tail) {
      /* We'll clear the buffer, most of the input was unwanted anyway if we got
       * that far. */
      tty_clear_buffer(tty);
      return -1;
    }
    char c = buf[i];
    tty->input_buffer[tty->input_head] = c;
    tty->input_head = next_head;
    if (c == '\n' || c == '\r') {
      cons_write(&c);
    } else if (c == '\b') {
      extern int col;
      col = col - 1;

    } else {
      cons_putchar(c);
    }
  }
  return length;
}

int tty_read(tty *tty, char *buf, int length) {
  int bytes_read = 0;

  while (bytes_read < length && tty->input_tail != tty->input_head) {
    buf[bytes_read] = tty->input_buffer[tty->input_tail];
    tty->input_tail = (tty->input_tail + 1) % 1024;
    bytes_read++;
  }

  return bytes_read;
}

void tty_clear_buffer(tty *tty) {
  for (int i = 0; i < 1024; i++) {
    tty->input_buffer[i] = 0;
  }
}

void tty_handle_key(tty *tty, char key) {
  int next_head = (tty->input_head + 1) % 1024;
  if (next_head == tty->input_tail) {
    return;
  }
  tty->input_buffer[tty->input_head] = key;
  tty->input_head = (tty->input_head + 1) % 1024;
  cons_putchar(key);
}