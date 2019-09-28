#pragma once
#include "component.h"

class ControllerComponent : public Component
{
public:
	ControllerComponent() 
	{
		m_event = "fire_weapon";
	}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new ControllerComponent(*this); }

	void Update() override;

protected:
	Name m_event;
};
