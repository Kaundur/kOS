#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "port.h"
#include "vga.h"

size_t terminal_row;
size_t terminal_column;

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

volatile uint16_t* terminal_buffer;

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}

void disable_cursor(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void update_cursor(int x, int y)
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void terminal_put_char_at(char c, size_t x, size_t y, uint8_t color) {
    const size_t buffer_index = y*VGA_WIDTH + x;
    terminal_buffer[buffer_index] = vga_entry(c, color);
}

void clear_terminal(void) {
    terminal_row = 0;
    terminal_column = 0;

    // Point the terminal_buffer at the section of memory that rendered to the screen by the hardware
    terminal_buffer = (uint16_t*) 0xB8000;

    uint8_t clear_color = vga_color(VGA_GRAY, VGA_BLACK);

    // Clear the screen
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', clear_color);
        }
    }
}

void terminal_initialize(void) {
    clear_terminal();
}

void render_splash_screen(void) {
    // Placeholder splash screen
    const char *logo[7];
    logo[0] = "dP       MMP\"\"\"\"\"YMM MP\"\"\"\"\"\"`MM";
    logo[1] = "88       M' .mmm. `M M  mmmmm..M";
    logo[2] = "88  .dP  M  MMMMM  M M.      `YM";
    logo[3] = "88888\"   M  MMMMM  M MMMMMMM.  M";
    logo[4] = "88  `8b. M. `MMM' .M M. .MMM'  M";
    logo[5] = "dP   `YP MMb     dMM Mb.     .dM";
    logo[6] = "         MMMMMMMMMMM MMMMMMMMMMM";

    // Offsets for the logo
    size_t start_x = 0;
    size_t start_y = 0;

    uint8_t logo_color = vga_color(VGA_GRAY, VGA_BLACK);

    // Render the logo
    for (size_t i=0; i<7; i++){
        size_t index = (start_y+i)*80 + start_x;
        size_t j = 0;
        while (logo[0][j]) {
            terminal_put_char_at(logo[i][j], start_x + j, start_y + i, logo_color);
            j++;
            index++;
        }
    }
}
