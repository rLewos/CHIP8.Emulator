#pragma once
#include <cstdint>
#include <array>
#include <string>
#include "Memory.h"

class CPU
{
public:
	CPU();
	~CPU();
	bool init();
	void reset();
	void runCicle();
	void loadCartridge(const std::string filePath);


private:
	std::array<uint8_t, 16> mRegisters;
	uint16_t mPC; // Pointer Counter.
	uint16_t mI;
	
	std::array<uint16_t, 16> mStack;
	uint8_t mSP; // Stack Pointer.

	uint8_t mDelayRegister;
	uint8_t mTimerRegister;
	uint8_t mSoundTimer;

	Memory mMemory;
};