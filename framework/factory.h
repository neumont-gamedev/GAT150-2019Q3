#pragma once
#include <string>
#include <map>

template<typename TBase>
class CreatorBase
{
public:
	virtual ~CreatorBase() {}
	virtual TBase* Create() const = 0;
};

template<typename T, typename TBase>
class Creator : public CreatorBase<TBase>
{
public:
	virtual TBase* Create() const 
	{ 
		return new T; 
	}
};

template<typename TBase>
class Spawner : public CreatorBase<TBase>
{
public:
	Spawner(TBase* instance) : m_instance(instance) {}
	virtual ~Spawner()
	{
		m_instance->Destroy();
		delete m_instance;
	}

	virtual TBase* Create() const { return m_instance->Clone(); }

private:
	TBase* m_instance = nullptr;
};

template<typename TBase, typename TKey = std::string>
class Factory
{
public:
	~Factory();

	template<typename T = TBase>
	T* Create(TKey key);
	void Register(TKey key, CreatorBase<TBase>* creator);

private:
	using registry_t = std::map<TKey, CreatorBase<TBase>*>;
	registry_t m_registry;
};

template<typename TBase, typename TKey>
inline Factory<TBase, TKey>::~Factory()
{
	for (auto& iter : m_registry)
	{
		delete iter.second;
	}

	m_registry.clear();
}

template<typename TBase, typename TKey>
template<typename T>
inline T* Factory<TBase, TKey>::Create(TKey key)
{
	auto iter = m_registry.find(key);
	if (iter == m_registry.end())
	{
		return nullptr;
	}

	CreatorBase<TBase>* creator = (*iter).second;

	return dynamic_cast<T*>(creator->Create());
}

template<typename TBase, typename TKey>
inline void Factory<TBase, TKey>::Register(TKey key, CreatorBase<TBase>* creator)
{
	if (m_registry.find(key) == m_registry.end())
	{
		m_registry[key] = creator;
	}
}
