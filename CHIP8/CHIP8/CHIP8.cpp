#include <iostream>
#include "CPU.h"

int main()
{
    CPU cpu;
    cpu.loadCartridge("E:\\Roms\\Chip8\\IBM Logo.ch8");
    cpu.runCicle();
}