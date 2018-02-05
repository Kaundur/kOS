#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tty.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, This needs to be compiled with a ix86-elf compiler"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif



void kernel_main(void)
{
    terminal_initialize();
    render_splash_screen();
}
