#pragma once
#include "event.h"
#include "system.h"

#include "..\\core\core.h"

#include <list>
#include <map>
#include <functional>

template <typename TEvent>
class EventDispatcher : public System
{
public:
	struct listener_t
	{
		Handle_t handle;
		std::function<bool(const TEvent&)> fp;

		bool operator == (const listener_t& other) const
		{
			return handle == other.handle;
		}
	};
	using listeners_t = std::list<listener_t>;

public:
	EventDispatcher(Engine* engine) : System(engine) {}

	virtual bool Startup() override { return true; }
	virtual void Shutdown() override 
	{
		for (auto iter : m_subscribers)
		{
			iter.second.clear();
		}
		m_subscribers.clear();
	}

	virtual void Update() override {}

	Handle_t Subscribe(const Name& name, std::function<bool(const TEvent&)> fp)
	{ 
		listener_t listener;
		listener.handle = ms_handle_id++;
		listener.fp = fp;

		m_subscribers[name].push_back(listener);

		return listener.handle;
	}

	void Unsubscribe(const Name& name, Handle_t handle)
	{
		auto iter = m_subscribers.find(name);
		if (iter != m_subscribers.end())
		{
			for (auto& listener : iter->second)
			{
				if (listener.handle == handle)
				{
					iter->second.remove(listener);
					break;
				}
			}
		}
	}

	void Notify(const TEvent& event, float time = 0.0f)
	{
		auto iter = m_subscribers.find(event.name);
		if (iter != m_subscribers.end())
		{
			listeners_t listeners = iter->second;
			for (auto listener : listeners)
			{
				listener.fp(event);
			}
		}
	}

protected:
	std::map<Name, listeners_t> m_subscribers;
	static Handle_t ms_handle_id;
};

template <typename TEvent>
Handle_t EventDispatcher<TEvent>::ms_handle_id = 0;
