// TODO - Need guard
#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "port.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

void keyboard_handler_main(void){
    // Test keyboard interrupt
    // If a key is pressed, read it and clear the screen
    char status;
    unsigned char scancode;

    outb(0x20, 0x20);

    status = inb(KEYBOARD_STATUS_PORT);
    if (status){
        scancode = inb(KEYBOARD_DATA_PORT);
        if (scancode == 0){
            return;
        }
        clear_terminal();
        // Enable cursor and place it at the 0, 0 coord
        // Use scanlines 12 to 13 for the cursor, this places it directly under a character
        enable_cursor(12, 13);
        update_cursor(0, 0);
    }

}