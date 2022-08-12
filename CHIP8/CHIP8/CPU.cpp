#include "CPU.h"

CPU::CPU()
{
	init();
}

CPU::~CPU()
{

}

bool CPU::init()
{
	bool hasInitialized = false;

	mRegisters = { 0 };
	mStack = { 0 };
	mPC = 0x200;
	mI = 0x0;
	mDelayRegister = 0x0;
	mSoundTimer = 0x0;
	mTimerRegister = 0x0;
	mSP = 0x0;
	mMemory.init();

	hasInitialized = true;

	return hasInitialized;
}

void CPU::reset()
{
	
}

void CPU::free()
{

}

void CPU::runCicle()
{
	uint16_t opcode = mMemory.read(mPC);

	switch (opcode)
	{
	case 0x0001:
		// Do something.
		break;

	default:
		break;
	}
}

void CPU::loadCartridge(const std::string filePath)
{
	std::ifstream fileCartridge{ filePath, std::ios::binary };
	std::vector<uint8_t> fileData;

	for (size_t i = 0; i < fileCartridge.width(); ++i)
	{
		
	}
}
