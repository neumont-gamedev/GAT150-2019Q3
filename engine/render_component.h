#pragma once
#include "component.h"

class RenderComponent : public Component
{
public:
	RenderComponent() : Component() {}

	virtual bool Load(const rapidjson::Value& value) override;

	virtual void Draw() = 0;

	static bool SortZ(const RenderComponent* lhs, const RenderComponent* rhs)
	{
		return lhs->m_z < rhs->m_z;
	}

protected:
	int m_z = 0;
};
