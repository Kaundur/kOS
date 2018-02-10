
#ifndef KOS_TTY_H
#define KOS_TTY_H

#include "port.h"

void clear_terminal(void);
void terminal_initialize(void);
void render_splash_screen(void);
void write_to_screen_buffer(size_t, uint16_t);
void disable_cursor(void);
void enable_cursor(uint8_t, uint8_t);
void update_cursor(uint8_t, uint8_t);

#endif //KOS_TTY_H