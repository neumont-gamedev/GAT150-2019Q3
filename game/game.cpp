#include "game.h"
#include "..\\engine\scene.h"
#include "..\\engine\text_component.h"

bool Game::Startup()
{
	bool success = m_engine->Startup();

	m_score_event = m_engine->GetSystem<EntityEventDispatcher>()->Subscribe("score", std::bind(&Game::OnScore, this, std::placeholders::_1));

	m_state_machine = new StateMachine<Game>(this);
	{
		State state;
		state.Enter = std::bind(&Game::TitleState_Enter, this);
		state.Update = std::bind(&Game::TitleState_Update, this);
		state.Exit = std::bind(&Game::TitleState_Exit, this);
		m_state_machine->AddState("game", state);
	}

	{
		State state;
		state.Enter = std::bind(&Game::StartState_Enter, this);
		state.Update = std::bind(&Game::StartState_Update, this);
		m_state_machine->AddState("start", state);
	}
	
	m_state_machine->SetState("start");

	return success;
}

void Game::Shutdown()
{
	m_engine->Shutdown();
	delete m_engine;

	delete m_state_machine;
}

void Game::Update()
{
	m_engine->Update();
	m_quit = m_engine->Quit();

	m_state_machine->Update();
}

void Game::TitleState_Enter()
{
	std::cout << "enter" << std::endl;
	m_engine->LoadScene("scenes/title.txt");

	//m_scene = new Scene();
	//m_scene->Create("game_scene", m_engine);

	//rapidjson::Document document;
	//bool success = json::load("scenes/title.txt", document);
	//ASSERT_MSG(success, "error loading scene json file.");
	//m_scene->Load(document);
}

void Game::TitleState_Update()
{
	//std::cout << "update" << std::endl;

	if (m_engine->GetSystem<InputSystem>()->GetKey(SDL_SCANCODE_SPACE))
	{
		m_state_machine->SetState("start");
	}
}

void Game::TitleState_Exit()
{
	m_engine->DestroyScene();
}

void Game::StartState_Enter()
{
	std::cout << "enter" << std::endl;
	m_lives = 4;
	m_score = 0;
	
	m_engine->LoadScene("scenes/scene.txt");

	for (size_t i = 0; i < 5; i++)
	{
		Entity* entity = m_engine->GetScene()->GetComponentFactory()->Create<Entity>("asteroid");
		entity->Initialize();
		entity->m_transform.translation = vector2(g_random(800.0f), g_random(600));
	
		m_engine->GetScene()->Add(entity);
	}
}

void Game::StartState_Update()
{
}

bool Game::OnScore(const Event<Entity>& event)
{
	m_score += event.variants[0].as_int;
	Entity* entity = m_engine->GetScene()->GetEntityWithName("score");
	std::string str = std::to_string(m_score);
	entity->GetComponent<TextComponent>()->CreateText(str.c_str());

	return true;
}
