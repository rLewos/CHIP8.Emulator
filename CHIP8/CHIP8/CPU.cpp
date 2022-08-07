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

void CPU::runCicle()
{

}

void CPU::loadCartridge(const std::string filePath)
{

}
