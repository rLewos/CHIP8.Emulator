#pragma once
#include <cstdint>
#include <array>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <random>

#include "Memory.h"
#include "RegistersEnum.h"
#include "KeyEnum.h"

class CPU
{
public:
	CPU();
	~CPU();
	bool init();
	void reset();
	void free();
	void runCicle();
	void loadCartridge(const std::string filePath);
	bool getHasDrawn();
	std::array<std::array<uint8_t,32>, 64> getScreen();
	void setKeyPressed(Keys keyPressed);
	void setKeyReleased(Keys keyPressed);
	void loadFonts();


private:
	std::array<uint8_t, 16> mRegisters; // GP Registers
	uint16_t mPC; // Pointer Counter.
	uint16_t mI;
	
	std::array<uint16_t, 16> mStack;
	uint8_t mSP; // Stack Pointer.

	uint8_t mDelayTimerRegister;
	uint8_t mSoundTimer;

	Memory mMemory; // RAM	
	std::array<std::array<uint8_t, 32>, 64> mScreen;
	bool mHasDrawn;
	std::array<std::uint8_t, 16> mKeypad;
	double mClock;

	uint64_t mCycles;
};