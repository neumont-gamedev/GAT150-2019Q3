#include "emitter_component.h"
#include "entity.h"
#include "..\\renderer\particle_system.h"

void EmitterComponent::Destroy()
{
}

bool EmitterComponent::Load(const rapidjson::Value& value)
{
	json::get_name(value, "texture_name", m_texture_name);

	json::get_int(value, "count", m_count);
	json::get_vector2(value, "lifetime_range", m_lifetime_range);
	json::get_vector2(value, "velocity_range", m_velocity_range);
	json::get_vector2(value, "angle_range", m_angle_range);
	json::get_float(value, "damping", m_damping);

	std::vector<std::string> tokens;
	json::get_strings(value, "action", '|', tokens);

	property_t<eAction> actions[] =
	{
		REFLECT_ENUM(STREAM),
		REFLECT_ENUM(BURST),
		REFLECT_ENUM(ORIENT_TO_VELOCITY)
	};
	m_action |= CreateBitMask<property_t<eAction>>(actions, sizeof(actions) / sizeof(property_t<eAction>), tokens);

	return true;
}

void EmitterComponent::Update()
{
	if (m_action[STREAM])
	{
		float spawn_rate = 1.0f / static_cast<float>(m_count);
		m_spawn_timer = m_spawn_timer + g_timer.dt();
		while (m_spawn_timer >= spawn_rate)
		{
			m_spawn_timer = m_spawn_timer - spawn_rate;

			SpawnParticle();
		}
	}
	else if (m_action[BURST])
	{
		m_action[BURST] = 0;
		for (int i = 0; i < m_count; i++)
		{
			SpawnParticle();
		}
	}
}

void EmitterComponent::SpawnParticle()
{
	float lifetime = g_random(m_lifetime_range[0], m_lifetime_range[1]);
	float velocity = g_random(m_velocity_range[0], m_velocity_range[1]);
	float angle = g_random(m_angle_range[0], m_angle_range[1]);

	vector2 random_direction = vector2::rotate(vector2::up, m_owner->m_transform.rotation + (angle * math::DEG_TO_RAD));
	vector2 v = random_direction * velocity;
	bit_mask_t state = (m_action[ORIENT_TO_VELOCITY]) ? bit_mask_t(BIT(Particle::ORIENT_TO_VELOCITY)) : 0;

	m_owner->GetOwner()->GetEngine()->GetSystem<ParticleSystem>()->Create(m_texture_name, m_owner->m_transform.translation, v, m_damping, lifetime, state);
}
