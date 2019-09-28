#pragma once
#include "component.h"

class AsteroidComponent : public Component
{
public:
	AsteroidComponent() {}

	void Initialize() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new AsteroidComponent(*this); }

	void Update() override;

	bool OnCollision(const Event<Entity>& entity);


protected:
	bool m_initialized = false;
	vector2 m_force;
	float m_torque;
	Handle_t m_collision_event;

	vector2 m_force_range;
	vector2 m_torque_range;
};

