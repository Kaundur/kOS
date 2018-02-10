#ifndef KOS_PORT_H
#define KOS_PORT_H

// Handles read/write of ports between the assembly and c
void outb(unsigned short port, unsigned char data);
char inb(unsigned short port);

#endif //KOS_PORT_H