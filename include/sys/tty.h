#ifndef TTY_H
#define TTY_H
typedef struct {
  char input_buffer[1024];
  int input_head;
  int input_tail;
} tty;
void tty_init(tty *tty);
int tty_read(tty *tty, char *buf, int length);
void tty_handle_key(tty *tty, char key);
int tty_write(tty *tty, char *buf, int length);
void tty_clear_buffer(tty *tty);
#endif