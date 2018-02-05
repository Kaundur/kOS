#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H



enum vga_color{
    VGA_BLACK 			= 0,
    VGA_BLUE 			= 1,
    VGA_GREEN 			= 2,
    VGA_CYAN 			= 3,
    VGA_RED  			= 4,
    VGA_MAGENTA 		= 5,
    VGA_BROWN 			= 6,
    VGA_GRAY 			= 7,
    VGA_DARK_GRAY		= 8,
    VGA_LIGHT_BLUE 		= 9,
    VGA_LIGHT_GREEN 	= 10,
    VGA_LIGHT_CYAN 		= 11,
    VGA_LIGHT_RED		= 12,
    VGA_LIGHT_MAGENTA 	= 13,
    VGA_YELLOW			= 14,
    VGA_WHITE			= 15,
};

// return a bit containing the color of the background and foreground color entered
static uint8_t vga_color(uint8_t fg, uint8_t bg){
    // Color information is stored in a single byte.
    // first four bits contain the background color, second 4 bits contain the foreground color
    return (uint8_t) fg | (uint8_t) bg << 4;
}

// return a value ready for entry into memory for a single character and its color binary value
static uint16_t vga_entry(unsigned char uc, uint8_t color) {
    // create a 16 bit entry for the screen, first byte is the color, second byte is the character.
    // Color should be set using vga_color
    return (uint16_t) uc | (uint16_t) color << 8;
}



#endif