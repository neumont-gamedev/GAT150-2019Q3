#pragma once

#include "..\\core\core.h"
#include "..\\math\vector2.h"
#include "..\\renderer\color.h"

struct Particle
{
	enum eState
	{
		ACTIVE,
		ORIENT_TO_VELOCITY
	};

	Name texture_name;
	vector2 position;
	vector2 velocity;
	float rotation = 0;
	float damping = 0.995f;
	float lifetime;
	bit_mask_t state;
};