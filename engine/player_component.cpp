#include "player_component.h"
#include "physics_component.h"
#include "entity.h"
#include "..\\core\random.h"
#include "..\\core\timer.h"

void PlayerComponent::Initialize()
{

	Entity* entity = m_owner->GetOwner()->GetComponentFactory()->Create<Entity>("ship_flame");
	entity->m_local_transform.translation = vector2(0.0f, -20.0f);
	entity->Initialize();

	m_owner->AddChild(entity);
}

void PlayerComponent::Destroy()
{
}

bool PlayerComponent::Load(const rapidjson::Value& value)
{
	json::get_float(value, "fire_rate", m_fire_rate);

	return true;
}

void PlayerComponent::Update()
{
	m_fire_timer -= g_timer.dt();
}

void PlayerComponent::Event(const Name& event)
{
	if (event == "fire_weapon" && m_fire_timer <= 0.0f)
	{
		m_fire_timer = m_fire_rate;

		Entity* entity = m_owner->GetOwner()->GetComponentFactory()->Create<Entity>("laser");
 		entity->m_transform.translation = m_owner->m_transform.translation;
		entity->m_transform.rotation = m_owner->m_transform.rotation;
		entity->Initialize();

		m_owner->GetOwner()->Add(entity);
	}
}
