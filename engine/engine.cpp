#include "engine.h"
#include "scene.h"
#include "entity.h"

#include "..\\core\filesystem.h"
#include "..\\core\name.h"
#include "..\\core\timer.h"
#include "..\\core\random.h"

#include <iostream>

bool Engine::Startup()
{
	ERR("Initializing Engine.");

	Name::InitializeNames();

	char pathname[256];
	filesystem::get_current_path(pathname, 256);
	std::cout << pathname << std::endl;
	filesystem::set_current_path("../");
	filesystem::get_current_path(pathname, 256);
	std::cout << pathname << std::endl;

	AudioSystem* audio_system = new AudioSystem(this);
	audio_system->Startup();
	m_systems.push_back(audio_system);

	Renderer* renderer = new Renderer(this);
	renderer->Startup();
	renderer->Create("game", 800, 600);
	m_systems.push_back(renderer);

	InputSystem* input_system = new InputSystem(this);
	input_system->Startup();
	m_systems.push_back(input_system);

	ParticleSystem* particle_system = new ParticleSystem(this);
	m_systems.push_back(particle_system);

	m_resource_manager = new ResourceManager<Resource>(renderer);

	EntityEventDispatcher* dispatcher = new EntityEventDispatcher(this);
	dispatcher->Startup();
	m_systems.push_back(dispatcher);

	return true;
}

void Engine::Shutdown()
{
	DestroyScene();

	delete m_resource_manager;

	for (System* system : m_systems)
	{
		system->Shutdown();
		delete system;
	}
	m_systems.clear();

	Name::ShutdownNames();

	SDL_Quit();
}

void Engine::Update()
{
	SDL_PumpEvents();
	SDL_Event e;
	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_quit = true;
		}
	}

	g_timer.tick();
	for (System* system : m_systems)
	{
		system->Update();
	}

	if (GetSystem<InputSystem>()->GetKey(SDL_SCANCODE_ESCAPE)) m_quit = true;


	if (m_scene) m_scene->Update();

	GetSystem<Renderer>()->BeginFrame();
	if (m_scene) m_scene->Draw();
	GetSystem<ParticleSystem>()->Draw();
	GetSystem<Renderer>()->EndFrame();
}

bool Engine::LoadScene(const char* scene)
{
	ASSERT(m_scene == nullptr);

	rapidjson::Document document;
	bool success = json::load(scene, document);
	ASSERT_MSG(success, "error loading scene json file.");

	m_scene = new Scene();
	m_scene->Create("game_scene", this);
	m_scene->Load(document);

	return success;
}

void Engine::DestroyScene()
{
	if (m_scene)
	{
		m_scene->Destroy();
		delete m_scene;
		m_scene = nullptr;
	}
}
