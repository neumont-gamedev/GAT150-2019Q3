#include "asteroid_component.h"
#include "physics_component.h"
#include "entity.h"
#include "..\\core\random.h"


void AsteroidComponent::Initialize()
{
	m_collision_event = m_owner->GetOwner()->GetEngine()->GetSystem<EntityEventDispatcher>()->Subscribe("collision", std::bind(&AsteroidComponent::OnCollision, this, std::placeholders::_1));

	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
	if (component)
	{
		float force = g_random(m_force_range[0], m_force_range[1]);
		m_force = vector2::rotate(vector2(0.0f, force), g_random(0.0f, math::TWO_PI));
		m_torque = g_random(m_torque_range[0], m_torque_range[1]) * math::DEG_TO_RAD;

		component->AddForce(m_force, PhysicsComponent::eForceType::VELOCITY);
		component->AddTorque(m_torque, PhysicsComponent::eForceType::VELOCITY);
	}
}

void AsteroidComponent::Destroy()
{
	m_owner->GetOwner()->GetEngine()->GetSystem<EntityEventDispatcher>()->Unsubscribe("collision", m_collision_event);
}

bool AsteroidComponent::Load(const rapidjson::Value& value)
{
	json::get_vector2(value, "force_range", m_force_range);
	json::get_vector2(value, "torque_range", m_torque_range);

	return true;
}

void AsteroidComponent::Update()
{
	//
}

bool AsteroidComponent::OnCollision(const Event<Entity>& event)
{
	if ((event.sender == m_owner || event.receiver == m_owner) && (event.sender->GetTag() == "player_weapon" || event.receiver->GetTag() == "player_weapon"))
	{
		m_owner->m_state.set(Entity::eState::DESTROY);

		Event<Entity> event;
		event.name = "score";
		event.variants[0].type = Variant::INT;
		event.variants[0].as_int = 100;

		m_owner->GetOwner()->GetEngine()->GetSystem<EntityEventDispatcher>()->Notify(event);
	}

	return true;
}
