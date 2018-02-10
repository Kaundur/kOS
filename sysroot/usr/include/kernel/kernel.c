#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "keyboard.h"


// Master PIC
#define PIC1_COMMAND 0x20
#define PIC1_DATA PIC1_COMMAND+1

// Slave PIC
#define PIC2_COMMAND 0xA0
#define PIC2_DATA PIC2_COMMAND+1

// Setup the interrupt controller
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08



#if defined(__linux__)
#error "You are not using a cross-compiler, This needs to be compiled with a ix86-elf compiler"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif



extern void keyboard_handler(void);
extern void load_idt(unsigned long *idt_ptr);

// Interrupt Descriptor Table (IDT)
// http://wiki.osdev.org/IDT
struct IDT_entry{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

// Initialise the interrupt controller for the keyboard
// http://wiki.osdev.org/8259_PIC
void init_pics(int pic1, int pic2){
    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    // X20 Master PIC command
    // X21 Master PIC data
    // XA0 Slave PIC command
    // XA1 Slave PIC data

    keyboard_address = (unsigned long)keyboard_handler;
    IDT[0x21].offset_lowerbits = keyboard_address;// & 0xffff;
    // Move to the correct segment of code, if this isnt assigned the kernel will restart
    IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = INTERRUPT_GATE;
    IDT[0x21].offset_higherbits = keyboard_address >> 16;

    /* send ICW1 */
    // Send the initalization code to the two pics 0X11
    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);

    /* send ICW2 */
    // Vector offset, PIC + 1..PIC + 8
    outb(PIC1_DATA, pic1);
    outb(PIC2_DATA, pic2);

    /* send ICW3 */
    // How its wired to master/slave
    // Tell master pic that there is a slave pic at IRQ2 (0000 0100)
    outb(PIC1_DATA, 4);
    // Tell slave its cascade identity (0000 00100)
    outb(PIC2_DATA, 2);

    /* send ICW4 */
    // Extra enviroment information
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    /* disable all IRQs */
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);

    idt_address = (unsigned long)IDT ;
    //idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + (idt_address << 16);
    idt_ptr[1] = idt_address >> 16 ;

    load_idt(idt_ptr);

    // Init IRQ1 keyboard
    outb(0x21 , 0xFD);
}



void kernel_main(void)
{
    terminal_initialize();

    init_pics(0x20, 0x28);

    render_splash_screen();
    disable_cursor();

    // Main kernel loop
    while(1){

    }
}
