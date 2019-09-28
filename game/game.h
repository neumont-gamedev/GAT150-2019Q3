#pragma once
#include "..\\engine\engine.h"
#include "..\\framework\state_machine.h"

class Game
{
public:
	Game(Engine* engine) : m_engine(engine) {}
	~Game() {}

	bool Startup();
	void Shutdown();
	void Update();

	bool Quit() { return m_quit; }

protected:
	void TitleState_Enter();
	void TitleState_Update();
	void TitleState_Exit();

	void StartState_Enter();
	void StartState_Update();

	bool OnScore(const Event<Entity>& event);

protected:
	size_t m_score = 0;
	size_t m_lives = 4;

	Handle_t m_score_event;

	bool m_quit = false;
	Engine* m_engine = nullptr;
	StateMachine<Game>* m_state_machine;
};
