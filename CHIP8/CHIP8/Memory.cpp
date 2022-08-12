#include "Memory.h"

Memory::Memory()
{
	init();
}

Memory::~Memory()
{

}

void Memory::init()
{
	mRAM = { 0 };
}

void Memory::write(uint16_t addressLocation, uint8_t data)
{
	mRAM.at(addressLocation) = data;
}

uint16_t Memory::read(uint16_t addressLocation)
{
	uint16_t data = mRAM.at(addressLocation);
	return data;
}
