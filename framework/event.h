#pragma once

#include "variant.h"
#include "..\\core\name.h"

template <typename T>
struct Event
{
	Event() {}

	Name name;
	T* sender = nullptr;
	T* receiver = nullptr;
	Variant variants[3];
};
