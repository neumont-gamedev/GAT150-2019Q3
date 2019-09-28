#pragma once

#include "..\\core\core.h"

#include "..\\renderer\renderer.h"
#include "..\\renderer\particle_system.h"
#include "..\\renderer\texture.h"
#include "..\\audio\audio_system.h"
#include "..\\input\input_system.h"
#include "..\\resources\resource_manager.h"
#include "..\\framework\event_dispatcher.h"

class Scene;
class Entity;

class EntityEventDispatcher : public EventDispatcher<Event<Entity>> 
{
public:
	EntityEventDispatcher(Engine* engine) : EventDispatcher<Event<Entity>>(engine) {}
};

class Engine
{
public:
	Engine() {}
	~Engine() {}

	bool Startup();
	void Shutdown();
	void Update();

	bool Quit() { return m_quit; }

	bool LoadScene(const char* scene);
	void DestroyScene();
	Scene* GetScene() { return m_scene; }

	template <typename T>
	T* GetSystem()
	{
		T* system = nullptr;
		for (System* _system : m_systems)
		{
			system = dynamic_cast<T*>(_system);
			if (system != nullptr) break;
		}

		return system;
	}
	
	ResourceManager<Resource>* GetResourceManager() { return m_resource_manager; }

private:
	bool m_quit = false;
	Scene* m_scene = nullptr;

	ResourceManager<Resource>* m_resource_manager = nullptr;
	std::vector<System*> m_systems;
};