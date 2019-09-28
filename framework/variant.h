#pragma once
#include "..\\math\vector2.h"
#include "..\\core\name.h"

struct Variant
{
	Variant() {}

	enum eType
	{
		INT,
		FLOAT,
		BOOL,
		VECTOR2,
		NAME
	};

	union
	{
		int as_int;
		float as_float;
		bool as_bool;
		vector2 as_vector2;
		Name as_name;
	};

	eType type;
};