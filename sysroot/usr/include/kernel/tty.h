
#ifndef KOS_TTY_H
#define KOS_TTY_H

#include "port.h"

//void terminal_clear (void);
void render_splash_screen(void);
void write_to_screen_buffer(size_t, uint16_t);
void terminal_initialize(void);
void disable_cursor(void);

#endif //KOS_TTY_H