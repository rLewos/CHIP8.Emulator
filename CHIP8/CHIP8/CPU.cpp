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
	mScreen = {0};
	mHasDrawn = false;

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
	mHasDrawn = false;
	uint16_t opcode = mMemory.fetchInstruction(mPC);

	std::cout << std::hex << opcode << "\n";
	switch (opcode >> 12)
	{
		case 0x0:

			std::cout << std::hex << (opcode & 0x00FF) << "\n";
			switch (opcode & 0x00FF)
			{
				case 0xE0:
				mScreen = { 0 };
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
			if (mRegisters[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
				mPC += 4;
			else 
				mPC += 2;

			break;

		case 0x5:
			if (mRegisters[(opcode & 0x0F00) >> 8] == mRegisters[(opcode & 0x00F0) >> 4])
				mPC += 4;
			else 
				mPC += 2;

			break;

		case 0x6:
			mRegisters[(opcode & 0x0F00) >> 8] = (uint8_t)(opcode & 0x00FF);
			mPC += 2;
			break;

		case 0x7:
			mRegisters[(opcode & 0x0F00) >> 8] += (uint8_t)(opcode & 0x00FF);
			mPC += 2;
			break;

		case 0x8:
			break;

		case 0x9:
			if (mRegisters[(opcode & 0x0F00) >> 8] != mRegisters[(opcode & 0x00F0) >> 4])
				mPC += 4;
			else
				mPC += 2;

			break;

		case 0xA:
			mI = (uint16_t)(opcode & 0x0FFF);
			mPC += 2;
			break;

		case 0xB:
			// Something is fishy here.
			// TODO: Review this instruction.
			mPC = (uint8_t)((opcode ^ 0xB000) + mRegisters[(uint8_t) Registers::V0]);
			break;

		case 0xC:
			// TODO
			mPC += 2;
			break;

		case 0xD:
		{
			uint8_t dataX = mRegisters[(opcode & 0x0F00) >> 8];
			uint8_t dataY = mRegisters[(opcode & 0x00F0) >> 4];
			uint8_t bytesToRead = (opcode & 0x000F);
			
			for (size_t i = 0; i < bytesToRead; i++)
			{
				uint8_t d = mMemory.read(mI + i);
				std::cout << "Pixel: " << std::hex << (int) d << "\n";
			}

			mHasDrawn = true;
			mPC += 2;
		}	
		break;

		case 0xE:
			mPC += 2;
			break;

		case 0xF:
			mPC += 2;
			break;

		default:
			std::cout << "Instruction '" << opcode << "' not implemented." << "\n";
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
		fileData.push_back(fileCartridge.get());
	}

	mMemory.writeBulk(mPC, fileData);
	fileCartridge.close();
}

bool CPU::getHasDrawn()
{
	return mHasDrawn;
}
