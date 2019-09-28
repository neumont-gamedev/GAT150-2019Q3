#pragma once

class Engine;

class System
{
public:
	System(Engine* engine) : m_engine(engine) {}
	virtual ~System() {}

	virtual bool Startup() { return true; }
	virtual void Shutdown() {}
	virtual void Update() {}

	Engine* GetEngine() { return m_engine; }
protected:
	Engine* m_engine;
};
