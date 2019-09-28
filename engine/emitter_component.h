#pragma once
#include "component.h"

class EmitterComponent : public Component
{
public:
	enum eAction
	{
		STREAM,
		BURST,
		ORIENT_TO_VELOCITY
	};

public:
	EmitterComponent() {}
	virtual ~EmitterComponent() {}

	void Destroy() override;
	virtual bool Load(const rapidjson::Value& value) override;
	virtual EmitterComponent* Clone() { return new EmitterComponent(*this); }

	virtual void Update() override;

protected:
	void SpawnParticle();

protected:
	Name m_texture_name;
	bit_mask_t  m_action;
	int m_count;
	vector2 m_lifetime_range;
	vector2 m_velocity_range;
	vector2 m_angle_range;
	float m_damping;

	float m_spawn_timer = 0.0f;

};
