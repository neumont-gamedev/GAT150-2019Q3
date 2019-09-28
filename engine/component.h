#pragma once
#include "object.h"

class Entity;

class Component : public Object
{
public:
	Component() {}
	void Create(const Name& name, Entity* owner) { m_name = name; m_owner = owner; }

	virtual void Update() = 0;
	
	Entity* GetOwner() { return m_owner; }
	void SetOwner(Entity* owner) { m_owner = owner; }

protected:
	Entity* m_owner;
};