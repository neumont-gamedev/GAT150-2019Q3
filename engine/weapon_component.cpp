#include "weapon_component.h"
#include "physics_component.h"
#include "entity.h"
#include "..\\core\random.h"
#include "..\\core\timer.h"

void WeaponComponent::Initialize()
{
	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
	if (component)
	{
		vector2 force = vector2::rotate(vector2(0.0f, m_force), m_owner->m_transform.rotation);
		component->AddForce(force, PhysicsComponent::eForceType::VELOCITY);
	}
}

void WeaponComponent::Destroy()
{
}

bool WeaponComponent::Load(const rapidjson::Value& value)
{
	json::get_float(value, "force", m_force);
	json::get_float(value, "rate", m_rate);
	json::get_float(value, "lifetime", m_lifetime);

	return true;
}

void WeaponComponent::Update()
{
	m_lifetime -= g_timer.dt();
	if (m_lifetime <= 0.0f)
	{
		m_owner->m_state[Entity::eState::DESTROY] = 1;
	}
}
