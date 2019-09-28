#include "transform.h"

bool transform::Load(const rapidjson::Value& value)
{
	json::get_vector2(value, "position", translation);
	json::get_float(value, "rotation", rotation);
	json::get_vector2(value, "scale", scale);

	return true;
}

void transform::Update()
{
	matrix33 mxs;
	mxs.scale(scale);

	matrix33 mxr;
	mxr.rotate(rotation);

	matrix33 mxt;
	mxt.translate(translation);

	mxWorld = mxs * mxr * mxt;
}

void transform::Update(const transform& parent_transform, const transform& local_transform)
{
	scale = parent_transform.scale * local_transform.scale;
	rotation = parent_transform.rotation + local_transform.rotation;
	translation = parent_transform.translation + vector2::rotate(local_transform.translation, rotation);

	Update();
}
