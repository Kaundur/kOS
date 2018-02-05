#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "port.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, This needs to be compiled with a ix86-elf compiler"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;

volatile uint16_t* terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;

    // Point the terminal_buffer at the section of memory that rendered to the screen by the hardware
    terminal_buffer = (uint16_t*) 0xB8000;

    uint8_t clear_color = vga_color(0, 0);

    // Clear the screen
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', clear_color);
        }
    }
}

void disable_cursor(void) {
    write_port(0x3D4, 0x0A);
    write_port(0x3D5, 0x20);
}

void render_splash(void) {
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
    size_t start_x = 24;
    size_t start_y = 9;

    uint8_t logo_color = vga_color(VGA_GREEN, VGA_BLACK);

    // Render the logo
    for (size_t i=0; i<7; i++){
        size_t index = (start_y+i)*80 + start_x;
        size_t j = 0;
        while (logo[0][j]) {
            terminal_buffer[index] = vga_entry(logo[i][j], logo_color);
            j++;
            index++;
        }
    }

    // Disable the cursor, as we only want to show the splash screen
    disable_cursor();
}

void kernel_main(void)
{
    terminal_initialize();
    render_splash();
}
