
#include "UIntPacker.h"
#include <iostream>

UCharPacker::UCharPacker()
{

}

UCharPacker::~UCharPacker()
{
}

unsigned char UCharPacker::Pack(unsigned char value, unsigned int bitCount)
{
	char data = 0;
	data = (data << bitCount) | value;
	return data;
}

unsigned int UCharPacker::Extract(unsigned char data, unsigned int bitCount)
{
	unsigned int value = data & ((1 << bitCount) - 1);
	data = data >> bitCount;
	return value;
}
