#include "entity.h"
#include "component.h"
#include "scene.h"
#include "render_component.h"


Entity::Entity(const Entity& entity)
{
	m_name = entity.m_name;
	m_scene = entity.m_scene;
	m_tag = entity.m_tag;
	m_transform = entity.m_transform;

	for (Component* component : entity.m_components)
	{
		Component* clone_component = dynamic_cast<Component*>(component->Clone());
		AddComponent(clone_component);
	}
}

void Entity::Initialize()
{
	for (Component* component : m_components)
	{
		component->Initialize();
	}
}

bool Entity::Create(const Name& name, Scene* scene)
{
	m_name = name;
	m_scene = scene;

	return true;
}

void Entity::Destroy()
{
	for (Component* component : m_components)
	{
		component->Destroy();
		delete component;
	}

	m_components.clear();
}

bool Entity::Load(const rapidjson::Value& value)
{
	json::get_name(value, "name", m_name);
	json::get_bool(value, "spawner", m_spawner);
	json::get_name(value, "tag", m_tag);
	json::get_float(value, "lifetime", m_lifetime);

	std::vector<std::string> strings;
	json::get_strings(value, "state", '|', strings);
	
	property_t<eState> states[] =
	{
		REFLECT_ENUM(ACTIVE),
		REFLECT_ENUM(VISIBLE),
		REFLECT_ENUM(TRANSIENT)
	};
	m_state |= CreateBitMask<property_t<eState>>(states, sizeof(states) / sizeof(property_t<eState>), strings);


	const rapidjson::Value& transform_value = value["transform"];
	if (transform_value.IsObject())
	{
		m_transform.Load(transform_value);
	}

	const rapidjson::Value& component_value = value["components"];
	if (component_value.IsArray())
	{
		LoadComponents(component_value);
	}

	return true;
}

void Entity::Update()
{
	if (m_state[TRANSIENT])
	{
		m_lifetime = m_lifetime - g_timer.dt();
		if (m_lifetime <= 0.0f)
		{
			m_state.set(DESTROY);
		}
	}

	for (Component* component : m_components)
	{
		component->Update();
	}

	if (m_parent)
	{
		m_local_transform.Update();
		m_transform.Update(m_parent->m_transform, m_local_transform);
	}
	else
	{
		m_transform.Update();
	}

	for (Entity* child : m_children)
	{
		child->Update();
	}
}

void Entity::Draw()
{
	RenderComponent* render_component = GetComponent<RenderComponent>();
	if (render_component)
	{
		render_component->Draw();
	}
}

void Entity::AddComponent(Component* component)
{
	ASSERT(component);
	ASSERT(std::find(m_components.begin(), m_components.end(), component) == m_components.end());

	component->SetOwner(this);
	m_components.push_back(component);
}

void Entity::RemoveComponent(Component* component)
{
	ASSERT(component);
	ASSERT(std::find(m_components.begin(), m_components.end(), component) != m_components.end());

	auto iter = std::find(m_components.begin(), m_components.end(), component);
	if (iter != m_components.end())
	{
		(*iter)->Destroy();
		delete* iter;

		m_components.erase(iter);
	}
}

void Entity::AddChild(Entity* child)
{
	child->m_parent = this;
	m_children.push_back(child);
}

bool Entity::LoadComponents(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++)
	{
		const rapidjson::Value& actor_value = value[i];
		if (actor_value.IsObject())
		{
			std::string type;
			if (json::get_string(actor_value, "type", type))
			{
				Component* component = m_scene->GetComponentFactory()->Create<Component>(type.c_str());
				ASSERT(component);
				if (component && component->Load(actor_value))
				{
					DEBUG1("Success creating (", type, ") component.");
					AddComponent(component);
				}
				else
				{
					ERR("Failure creating (", type, ") component.");
				}
			}
		}
	}

	return true;
}
