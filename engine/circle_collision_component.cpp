#include "circle_collision_component.h"
#include "entity.h"

void CircleCollisionComponent::Create(const Name& name, Entity* owner, float radius)
{
}

void CircleCollisionComponent::Destroy()
{
}

bool CircleCollisionComponent::Load(const rapidjson::Value& value)
{
	json::get_float(value, "radius", m_radius);

	return true;
}

void CircleCollisionComponent::Update()
{
}

bool CircleCollisionComponent::Intersects(CollisionComponent* other)
{
	bool intersects = false;

	CircleCollisionComponent* component = dynamic_cast<CircleCollisionComponent*>(other);
	if (component)
	{
		float distance = vector2::distance(m_owner->m_transform.translation, other->GetOwner()->m_transform.translation);
		if (distance <= m_radius + component->m_radius)
		{
			intersects = true;
		}
	}

	return intersects;
}
