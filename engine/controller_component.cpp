#include "controller_component.h"
#include "physics_component.h"
#include "player_component.h"
#include "entity.h"
#include "..\\external\SDL2-2.0.10\include\SDL.h"

void ControllerComponent::Destroy()
{
}

bool ControllerComponent::Load(const rapidjson::Value& value)
{
	return true;
}

void ControllerComponent::Update()
{
	const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

	float torque = 0.0f;
	vector2 force = vector2::zero;

	if (keyboard_state[SDL_SCANCODE_A]) torque -= 20.0f;
	if (keyboard_state[SDL_SCANCODE_D]) torque += 20.0f;
	if (keyboard_state[SDL_SCANCODE_W]) force.y += 600.0f;
	if (keyboard_state[SDL_SCANCODE_S]) force.y -= 600.0f;

	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
	if (component)
	{
		vector2 force_ = vector2::rotate(force, m_owner->m_transform.rotation);

		component->AddForce(force_, PhysicsComponent::eForceType::FORCE);
		component->AddTorque(torque, PhysicsComponent::eForceType::FORCE);
	}

	if (keyboard_state[SDL_SCANCODE_SPACE])
	{
		PlayerComponent* component = m_owner->GetComponent<PlayerComponent>();
		if (component)
		{
			component->Event(m_event);
		}
	}
}
