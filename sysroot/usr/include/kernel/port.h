#ifndef _KERNEL_PORT_H
#define _KERNEL_PORT_H

// Handles read/write of ports between the assembly and c
void write_port(unsigned short port, unsigned char data);
char read_port(unsigned short port);

#endif