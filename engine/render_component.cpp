#include "render_component.h"

bool RenderComponent::Load(const rapidjson::Value& value)
{
	json::get_int(value, "z", m_z);

	return true;
}
