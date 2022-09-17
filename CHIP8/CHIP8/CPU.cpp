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

	switch (opcode >> 12)
	{
		case 0x0:
			switch (opcode & 0x00FF)
			{
				case 0xE0:
					break;

				case 0xEE:
					mSP -= 1;
					mPC = mStack[mSP];
					break;
			}

			mPC += 2;
			break;

		case 0x1:
			mPC = (opcode & 0x0FFF);
			break;

		case 0x2:
			mStack[mSP] = mPC;
			mSP += 1;

			mPC = (opcode & 0x0FFF);
			break;

		case 0x3:
			
			if (mRegisters[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
				mPC += 4;
			else
				mPC += 2;

			break;

		case 0x4:

			break;


		default:
			break;
	}
}

void CPU::loadCartridge(std::string filePath)
{
	if (filePath.empty())
	{
		throw std::exception("File path is empty.");
	}

	std::ifstream fileCartridge{ filePath, std::ios::binary };
	if (!fileCartridge)
	{
		throw std::exception("File not found.");
	}
	
	std::vector<uint8_t> fileData;
	while (fileCartridge)
	{
		std::string file;
		fileCartridge >> file;
		std::cout << file << "\n";
	}

	mMemory.write(mPC, 0x0);
	fileCartridge.close();
}
