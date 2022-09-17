#pragma once
#include <cstdint>
#include <array>

class Memory
{
public:
	Memory();
	~Memory();
	void init();
	void reset();

	void write(uint16_t addressLocation, uint8_t data);
	void write(uint16_t addressLocation, uint8_t* data);
	uint16_t read(uint16_t addressLocation);

private:
	std::array<uint8_t, 4096> mRAM;
};