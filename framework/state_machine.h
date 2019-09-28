#pragma once

#include "..\\core\core.h"
#include <functional>
#include <map>

struct State
{
	std::function<void()> Enter;
	std::function<void()> Update;
	std::function<void()> Exit;
};

template <typename T>
class StateMachine
{
public:
	StateMachine(T* owner) : m_owner(owner) {}
	~StateMachine() {}

	void Update();
	void AddState(const Name& name, const State& state);
	void AddState(const Name& name, std::function<void()> enter, std::function<void()> update, std::function<void()> exit);
	void SetState(const Name& name);

private:
	T* m_owner = nullptr;

	State* m_state = nullptr;
	std::map<Name, State> m_states;
};

template<typename T>
inline void StateMachine<T>::Update()
{
	if (m_state)
	{
		if (m_state->Update) m_state->Update();
	}
}

template<typename T>
inline void StateMachine<T>::AddState(const Name& name, const State& state)
{
	assert(m_states.find(name) == m_states.end());

	m_states[name] = state;
}

template<typename T>
inline void StateMachine<T>::AddState(const Name& name, std::function<void()> enter, std::function<void()> update, std::function<void()> exit)
{
	assert(m_states.find(name) == m_states.end());

	State state;
	state.Enter = enter;
	state.Update = update;
	state.Exit = exit;

	m_states[name] = state;
}

template<typename T>
inline void StateMachine<T>::SetState(const Name& name)
{
	if (m_states.find(name) != m_states.end())
	{
		State* new_state = &m_states[name];
		if (new_state != m_state)
		{
			if (m_state)
			{
				if (m_state->Update) m_state->Exit();
			}
			m_state = new_state;
			if (m_state->Enter) m_state->Enter();
			if (m_state->Update) m_state->Update();
		}
	}
}
