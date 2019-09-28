#include "animation_component.h"
#include "entity.h"

void AnimationComponent::Initialize()
{
}

void AnimationComponent::Destroy()
{
}

bool AnimationComponent::Load(const rapidjson::Value& value)
{
	json::get_float(value, "time_scale", m_time_scale);

	std::vector<std::string> strings;
	json::get_strings(value, "action", '|', strings);

	property_t<eAction> actions[] =
	{
		REFLECT_ENUM(ONE_TIME),
		REFLECT_ENUM(ONE_TIME_DESTROY_OWNER),
		REFLECT_ENUM(LOOP),
		REFLECT_ENUM(PING_PONG),
		REFLECT_ENUM(REVERSE)
	};
	m_action |= CreateBitMask<property_t<eAction>>(actions, sizeof(actions) / sizeof(property_t<eAction>), strings);

	return true;
}

void AnimationComponent::Update()
{
	float d = (m_forward) ? 1.0f : -1.0f;
	m_time += g_timer.dt() * (d * m_time_scale);

	if (m_time < 0.0f || m_time > 1.0f)
	{
		if (m_action[LOOP])
		{
			if (m_action[PING_PONG])
			{
				m_forward = !m_forward;
				m_time = (m_forward) ? 0.0f : 1.0f;
			}
			else
			{
				if (m_forward) m_time = 0.0f;
				else m_time = 1.0f;
			}
		}
		else if (m_action[ONE_TIME] || m_action[ONE_TIME_DESTROY_OWNER])
		{
			m_time = (m_action[REVERSE]) ? 0.0f : 1.0f;
			if (m_action[ONE_TIME_DESTROY_OWNER])
			{
				m_owner->m_state[Entity::DESTROY] = 1;
			}
		}
	}
}

/*
if ((time_ < 0.0f || time_ > 1.0f)) {
		if (action_[kRepeat]) {
			if (action_[kPlayBack]) {
				action_[kReverse] = !action_[kReverse];
			}
			time_ = (!action_[kReverse] ? 0.0f : 1.0f);
		} else {
			if (action_[kPlayBack]) {
				if (action_[kDestroyOwner]) owner_->state_[Entity::kDestroy] = completed_;
				completed_ = !completed_;
				action_[kReverse] = !action_[kReverse];
			} else {
				if (action_[kDestroyOwner]) owner_->state_[Entity::kDestroy] = true;
			}
		}
*/