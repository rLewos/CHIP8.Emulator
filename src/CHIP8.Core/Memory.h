#include <cstdint>
#include <array>
#include <vector>
#include <cstdint>

class Memory
{
public:
	Memory();
	~Memory();
	void init();
	void reset();

	void write(uint16_t addressLocation, uint8_t data);
	void writeBulk(uint16_t addressLocation, const std::vector<uint8_t>& bulk);
	uint16_t fetchInstruction(uint16_t addressLocation);
	uint8_t read(uint16_t addressLocation);

private:
	std::array<uint8_t, 4096> mRAM;
};