	#pragma once

#include "..\\core\json.h"
#include "matrix33.h"

struct transform
{
	vector2 translation = vector2::zero;
	float rotation = 0.0f;
	vector2 scale = vector2::one;
	matrix33 mxWorld;

	transform() {}
	transform(vector2& translation, float rotation, vector2 scale) : 
		translation(translation), 
		rotation(rotation), 
		scale(scale) {}

	bool Load(const rapidjson::Value& value);
	void Update();
	void Update(const transform& parent_transform, const transform& local_transform);
};
