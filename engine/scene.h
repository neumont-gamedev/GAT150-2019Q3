#pragma once
#include "object.h"
#include "engine.h"
#include "component.h"
#include "entity.h"
#include "..\\renderer\text.h"
#include "..\\framework\factory.h"
#include <list>


class ComponentFactory : public Factory<Object, Name> {};

class Scene : public Object
{
public:
	Scene() {}

	bool Create(const Name& name, Engine* engine);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Scene* Clone() override { return new Scene(*this); }

	void Update();
	void Draw();
	
	void Add(Entity* entity);
	std::list<Entity*>::iterator Remove(Entity* entity, bool destroy = true);

	Entity* GetEntityWithName(const Name& name);
	std::vector<Entity*> GetEntitiesWithTag(const Name& tag);

	template<typename T>
	std::vector<T*> GetEntityComponents()
	{
		std::vector<T*> components;

		for (Entity* entity : m_entities)
		{
			T* component = nullptr;// entity->GetComponent<T>();
			if (component)
			{
				components.push_back(component);
			}
		}

		return components;
	}

	ComponentFactory* GetComponentFactory() { return m_component_factory; }
	Engine* GetEngine() { return m_engine; }

	friend class Entity;

protected:
	bool LoadEntities(const rapidjson::Value& value);

protected:
	std::list<Entity*> m_entities;

	ComponentFactory* m_component_factory;
	Engine* m_engine;
};