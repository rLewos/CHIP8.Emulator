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

void Memory::writeBulk(uint16_t addressLocation, const std::vector<uint8_t>& bulk)
{
	uint32_t bulkSize = bulk.size();
	for (size_t i = 0; i < bulkSize; i++)
	{
		mRAM.at(addressLocation + i) = bulk.at(i);
	};
}

uint16_t Memory::fetchInstruction(uint16_t addressLocation)
{
	uint8_t data1 = mRAM.at(addressLocation);
	uint8_t data2 = mRAM.at(addressLocation + 1);
	uint16_t data = (data1 << 8) + (data2);

	return data;
}

uint8_t Memory::read(uint16_t addressLocation)
{
	return mRAM.at(addressLocation);
}
