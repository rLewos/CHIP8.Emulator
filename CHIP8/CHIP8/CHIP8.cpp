#include <iostream>
#include "CPU.h"

int main()
{
	try
	{
		CPU cpu;
		cpu.loadCartridge("E:\\Roms\\Chip8\\IBM Logo.ch8");
		
		while (true) {
			cpu.runCicle();
		}

		
	}
	catch (const std::exception& e)
	{
		printf("Error: %s", e.what());
	}
}