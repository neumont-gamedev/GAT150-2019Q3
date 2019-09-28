#pragma once
#include "..\\core\core.h"

struct Handle
{
	Handle() : index(0), counter(0), type(0) {}
	Handle(u32 index, u32 counter, u32 type = 0) : index(index), counter(counter), type(type)	{}

	inline operator u32() const { return type << 27 | counter << 12 | index; }

	u32 index	: 12;
	u32 counter	: 15;
	u32 type	: 5;
};
