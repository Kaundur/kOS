all:
	i686-elf-as ./sysroot/usr/include/kernel/boot.s -o ./sysroot/usr/include/kernel/boot.o
	i686-elf-gcc -c ./sysroot/usr/include/kernel/kernel.c -o ./sysroot/usr/include/kernel/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T ./sysroot/usr/include/kernel/linker.ld -o ./sysroot/usr/include/kernel/kOS.bin -ffreestanding -O2 -nostdlib ./sysroot/usr/include/kernel/boot.o ./sysroot/usr/include/kernel/kernel.o -lgcc
