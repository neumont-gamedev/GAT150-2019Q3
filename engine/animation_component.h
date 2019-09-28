#pragma once
#include "component.h"

class AnimationComponent : public Component
{
public:
	enum eAction
	{
		ONE_TIME,
		ONE_TIME_DESTROY_OWNER,
		LOOP,
		PING_PONG,
		REVERSE
	};

public:
	AnimationComponent() {}

	void Initialize() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new AnimationComponent(*this); }

	void Update() override;

	float GetTime() { return m_time; }
	void SetTimeScaleFrame(int fps) { m_time_scale = static_cast<float>(fps) / 60.0f; }
	void SetTimeScale(float time_scale) { m_time_scale = time_scale; }
	float GetTimeScale() { return m_time_scale; }

protected:
	bit_mask_t m_action = BIT(LOOP);
	bool m_forward = true;
	float m_time = 0.0f;
	float m_time_scale = 1.0f;
};