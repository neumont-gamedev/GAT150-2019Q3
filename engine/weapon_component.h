#pragma once
#include "component.h"

class WeaponComponent : public Component
{
public:
	WeaponComponent() {}

	void Initialize() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new WeaponComponent(*this); }

	void Update() override;

protected:
	float m_force;
	float m_rate;

	float m_lifetime;
};

