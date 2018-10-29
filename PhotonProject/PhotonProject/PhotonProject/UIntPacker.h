
#pragma once

class UCharPacker
{
public:
	UCharPacker();
	~UCharPacker();

	unsigned char Pack(unsigned char value, unsigned int bitCount);
	unsigned int Extract(unsigned char data, unsigned int bitCount);
};