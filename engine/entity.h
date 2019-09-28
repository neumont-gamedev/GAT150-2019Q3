#pragma once
#include "object.h"
#include "scene.h"
#include "..\\math\transform.h"
#include "..\\core\core.h"

class Component;

class Entity : public Object
{
public:
	enum eState
	{
		ACTIVE,
		VISIBLE,
		DESTROY,
		TRANSIENT,
	};

public:
	Entity() {}
	Entity(const Entity& entity);
	virtual ~Entity() {}
	
	bool Create(const Name& name, Scene* scene);

	void Initialize() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;

	Entity* Clone() override { return new Entity(*this); }

	void Update();
	void Draw();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template <typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* _component : m_components)
		{
			component = dynamic_cast<T*>(_component);
			if (component != nullptr) break;
		}

		return component;
	}

	void SetTag(const Name& tag) { m_tag = tag; }
	const Name& GetTag() const { return m_tag; }

	Scene* GetOwner() { return m_scene; }
	void SetOwner(Scene* scene) { m_scene = scene; }

	void AddChild(Entity* entity);
	std::vector<Entity*>& GetChildren() { return m_children; }
	Entity* GetParent() { return m_parent; }

	bool IsSpawner() { return m_spawner; }

	friend class Scene;
	friend class Component;

protected:
	bool LoadComponents(const rapidjson::Value& value);

public:
	transform m_transform;
	transform m_local_transform;
	bit_mask_t m_state = BIT(eState::ACTIVE) | BIT(eState::VISIBLE);

protected:
	Name m_tag;
	Scene* m_scene = nullptr;
	bool m_spawner = false;
	float m_lifetime = 0;
	
	Entity* m_parent = nullptr;
	std::vector<Entity*> m_children;
	std::vector<Component*> m_components;
};
