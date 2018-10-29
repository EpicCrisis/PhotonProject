
#pragma once

class UCharPacker
{
private:
	unsigned int m_data;
	unsigned int m_bitCount; // To count how many bits are used.

public:
	UCharPacker();
	~UCharPacker();

	// Pack the "value" into m_data, it returns true if there are enough bits available 
	// BitCount : the bit count of "value"
	bool Pack(unsigned char value, unsigned int bitCount);
	unsigned int Extract(unsigned int bitCount);

	unsigned int GetData();
};