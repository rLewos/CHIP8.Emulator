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

	loadFonts();
	mRegisters = { 0 };
	mStack = { 0 };
	mPC = 0x200;
	mI = 0x0;
	mDelayTimerRegister = 0x0;
	mSoundTimer = 0x0;
	mSP = 0x0;
	mMemory.init();
	mScreen = { 0 };
	mHasDrawn = false;
	mKeypad = { 0 };
	mCycles = 0;
	mClock = 1;

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

	std::cout  << mCycles << ": " << std::hex << opcode << "\n";

	if (mDelayTimerRegister > 0)
		--mDelayTimerRegister;

	if (mSoundTimer > 0)
		--mSoundTimer;	

	switch (opcode >> 12)
	{
	case 0x0:

		std::cout << std::hex << (opcode & 0x00FF) << "\n";
		switch (opcode & 0x00FF)
		{
		case 0xE0:
			mScreen = { 0 };
			mHasDrawn = true;
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

		switch (opcode & 0x000F)
		{
		case 0x0:
			mRegisters[(opcode & 0x0F00) >> 8] = mRegisters[(opcode & 0x00F0) >> 4];
			break;

		case 0x1:
			mRegisters[(opcode & 0x0F00) >> 8] = (uint8_t) (mRegisters[(opcode & 0x0F00) >> 8] | mRegisters[(opcode & 0x00F0) >> 4]);
			break;

		case 0x2:
			mRegisters[(opcode & 0x0F00) >> 8] = (uint8_t) (mRegisters[(opcode & 0x0F00) >> 8] & mRegisters[(opcode & 0x00F0) >> 4]);
			break;

		case 0x3:
			mRegisters[(opcode & 0x0F00) >> 8] ^= mRegisters[(opcode & 0x00F0) >> 4];
			break;

		case 0x4:
		{
			uint8_t dataX = mRegisters[(opcode & 0x0F00) >> 8];
			uint8_t dataY = mRegisters[(opcode & 0x00F0) >> 4];

			mRegisters[(opcode & 0x0F00) >> 8] += mRegisters[(opcode & 0x00F0) >> 4];

			if ((dataX + dataY) > sizeof(uint8_t))
				mRegisters[(int)Registers::VF] = 0x1;
			else
				mRegisters[(int)Registers::VF] = 0x0;
		}
		break;

		case 0x5:
		{
			uint8_t dataX = mRegisters[(opcode & 0x0F00) >> 8];
			uint8_t dataY = mRegisters[(opcode & 0x00F0) >> 4];

			mRegisters[(opcode & 0x0F00) >> 8] -= mRegisters[(opcode & 0x00F0) >> 4];

			if ((dataY - dataX) < 0)
				mRegisters[(int)Registers::VF] = 0x0;
			else
				mRegisters[(int)Registers::VF] = 0x1;
		}
		break;

		case 0x6:
		{
			uint8_t dataYPriorShift = mRegisters[(opcode & 0x00F0) >> 4];
			mRegisters[(opcode & 0x0F00) >> 8] = (mRegisters[(opcode & 0x00F0) >> 4]) >> 1;

			uint8_t flag = (dataYPriorShift & 0b00000001);
			mRegisters[(int)Registers::VF] = flag;
		}
		break;

		case 0x7:
		{
			uint8_t dataX = mRegisters[(opcode & 0x0F00) >> 8];
			uint8_t dataY = mRegisters[(opcode & 0x00F0) >> 4];

			mRegisters[(opcode & 0x0F00) >> 8] = mRegisters[(opcode & 0x00F0) >> 4] - mRegisters[(opcode & 0x0F00) >> 8];

			if ((dataY - dataX) < 0)
				mRegisters[(int)Registers::VF] = 0x0;
			else
				mRegisters[(int)Registers::VF] = 0x1;
		}
		break;

		case 0xE:
		{
			uint8_t dataYPriorShift = mRegisters[(opcode & 0x00F0) >> 4];
			mRegisters[(opcode & 0x0F00) >> 8] = (mRegisters[(opcode & 0x00F0) >> 4]) << 1;

			uint8_t flag = ((dataYPriorShift & 0b10000000) >> 8);
			mRegisters[(int)Registers::VF] = flag;
		}
		break;
		}

		mPC += 2;
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
		mPC = (uint8_t)((opcode & 0x0FFF) + mRegisters[(uint8_t)Registers::V0]);
		break;

	case 0xC:
	{
		uint8_t mask = (opcode & 0x00FF);
		uint8_t randomNumber = rand() % 0xFF; // Range: 0x00 to 0xFF.
		mRegisters[(opcode & 0x0F00) >> 8] = (randomNumber & mask);
		mPC += 2;
	}
	break;

	case 0xD:
	{
		// TODO
		uint8_t dataX = mRegisters[(opcode & 0x0F00) >> 8];
		uint8_t dataY = mRegisters[(opcode & 0x00F0) >> 4];
		uint8_t bytesToRead = (opcode & 0x000F);

		for (size_t y = 0; y < bytesToRead; y++)
		{
			// The interpreter reads n bytes from memory, starting at the address stored in I. 
			uint8_t pixelByte = mMemory.read(mI + y);
			
			for (size_t x = 0; x < 8; x++)
			{
				if (mCycles > 7 && x > 5)
					std::cout << "\n";

				// Last frame pixel.
				uint8_t screenCurrentPixel = 0;
				if (dataX + x > 63)
				{
					std::cout << "\n";
					uint8_t wrappedPixel = (dataX + x) - 64;
					screenCurrentPixel = mScreen[wrappedPixel][dataY + y];
				}
				else {
					screenCurrentPixel = mScreen[dataX + x][dataY + y];
				}

				
				// Sprites are XORed onto the existing screen. 
				uint8_t xoredPx = screenCurrentPixel ^ 0x1;
				
				if ((pixelByte & (0x80 >> x)) != 0)
				{
					// Check each bit from byte-sprite.
					// These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). 
					mScreen[dataX + x][dataY + y] = xoredPx;
				}

				if ((screenCurrentPixel == 0x1) && (xoredPx == 0x0))
					mRegisters[(int32_t)Registers::VF] = 0x1;
				else 
					mRegisters[(int32_t)Registers::VF] = 0x0;
			}
		}

		mHasDrawn = true;
		mPC += 2;
	}
	break;

	case 0xE:

		switch (opcode & 0x00FF)
		{
			case 0x9E:
			{
				uint8_t key = mRegisters[(opcode & 0x0F00) >> 8];
				if (mKeypad[key] != 0)
					mPC += 4;
				else 
					mPC += 2;
			}
			break;

			case 0xA1:
			{
				uint8_t key = mRegisters[(opcode & 0x0F00) >> 8];
				if (mKeypad[key] == 0)
					mPC += 4;
				else
					mPC += 2;
			}
			break;

			default:
				break;
		}
		break;

	case 0xF:
		switch (opcode & 0x00FF)
		{
		case 0x07:
			mRegisters[(opcode & 0x0F00) >> 8] = mDelayTimerRegister;
			break;

		case 0x0A:
		{
			uint8_t target = (opcode & 0x0F00) >> 8;
			uint8_t buttonSize = mKeypad.size();

			bool hasButtonPressed = false;
			for (size_t i = 0; i < buttonSize; i++)
			{
				if (mKeypad[i] == 0x1)
				{
					mRegisters[target] = i;
					hasButtonPressed = true;
					break;
				}
			}

			if (!hasButtonPressed)
				return;
		}
		break;

		case 0x15:
			mDelayTimerRegister = mRegisters[(opcode & 0x0F00) >> 8];
			break;

		case 0x18:
			mSoundTimer = mRegisters[(opcode & 0x0F00) >> 8];
			break;

		case 0x1E:
			mI += mRegisters[(opcode & 0x0F00) >> 8];
			break;

		case 0x29:
			mI = mRegisters[(opcode & 0x0F00) >> 8];
			break;

		case 0x33:
		{
			uint8_t value = mRegisters[(opcode & 0x0F00) >> 8];

			uint8_t firstDigit = value / 100;
			uint8_t secDigit = (value / 10) % 10;
			uint8_t thirdDigit = (value % 100) % 10;

			mMemory.write(mI, firstDigit);
			mMemory.write(mI + 1, secDigit);
			mMemory.write(mI + 2, thirdDigit);
		}
		break;

		case 0x55:
			{
				uint8_t numRegisters = (opcode & 0x0F00) >> 8;
				
				for (size_t r = 0; r <= numRegisters; r++)
					mMemory.write(mI + r, mRegisters[r]);

				mI +=  numRegisters + 1;
			}
			break;

		case 0x65:
			{
			// TODO
				uint8_t numRegisters = (opcode & 0x0F00) >> 8;
				
				for (size_t r = 0; r <= numRegisters; r++)
					mRegisters[r] = mMemory.read(mI + r);

				mI = mI + numRegisters + 1;
			}
			break;

		default:
			break;
		}

		mPC += 2;
		break;

	default:
		std::cout << "Instruction '" << opcode << "' not implemented." << "\n";
		break;
	}

	++mCycles;
}

void CPU::loadCartridge(std::string filePath)
{
	if (filePath.empty())
	{
		throw std::exception("File path is empty.");
	}

	std::ifstream fileCartridge{ filePath, std::ios::binary };
	if (!fileCartridge) // '!' overrides 'fail() -> bool'
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

std::array<std::array<uint8_t, 32>, 64> CPU::getScreen()
{
	return mScreen;
}

void CPU::setKeyPressed(Keys keyPressed)
{
	mKeypad[(uint8_t)keyPressed] = 0x1;
}

void CPU::setKeyReleased(Keys keyPressed)
{
	mKeypad[(uint8_t)keyPressed] = 0x0;
}

void CPU::loadFonts()
{
	uint8_t fonts[5 * 16] = {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20 ,0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	mPC = 0x50;
	int8_t fontSize = sizeof(fonts);
	for (size_t i = 0; i < fontSize; i++)
		mMemory.write(mPC + i , fonts[i]);
}
