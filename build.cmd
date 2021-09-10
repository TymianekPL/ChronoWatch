@echo off
cls
echo Building and running (%TIME%)
wsl nasm -f bin boot.asm -o boot.bin
wsl nasm -f elf64 loader.asm -o loader.o

wsl #cc -m64  -ffreestanding -fno-builtin -nostdlib -c kernel.c
wsl cc -m64 -masm=intel -c kernel.c
wsl ld  -Ttext 0x100000 -o kernel.elf loader.o kernel.o
wsl objcopy -R .note -R .comment -S -O binary kernel.elf kernel.bin

wsl dd if=/dev/zero of=image.bin bs=512 count=2880
wsl dd if=boot.bin of=image.bin conv=notrunc
wsl dd if=kernel.bin of=image.bin conv=notrunc bs=512 seek=1

@rem wsl iat image.bin image.iso

wsl rm ./boot.bin ./kernel.bin ./loader.o ./kernel.elf ./kernel.o

qemu-system-x86_64.exe -drive file=image.bin,format=raw