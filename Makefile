ARCHDIR = ./sysroot/usr/include/kernel

clean:
	-rm $(ARCHDIR)/*.o
	-rm $(ARCHDIR)/*.bin
all: clean
	i686-elf-as $(ARCHDIR)/boot.s -o $(ARCHDIR)/boot.o
	i686-elf-gcc -c $(ARCHDIR)/tty.c -o $(ARCHDIR)/tty.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(ARCHDIR)/kernel.c -o $(ARCHDIR)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T $(ARCHDIR)/linker.ld -o $(ARCHDIR)/kOS.bin -ffreestanding -O2 -nostdlib $(ARCHDIR)/boot.o $(ARCHDIR)/kernel.o $(ARCHDIR)/tty.o -lgcc
