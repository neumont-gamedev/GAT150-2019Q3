#include "handle_manager.h"

HandleManager::HandleManager()
{
	Reset();
}

void HandleManager::Reset()
{
	m_active_count = 0;
	m_first_free_entry = 0;

	for (int i = 0; i < MAX_ENTRIES - 1; ++i)
	{
		m_entries[i] = HandleEntry(i + 1);
	}
	m_entries[MAX_ENTRIES - 1] = HandleEntry();
	m_entries[MAX_ENTRIES - 1].end = true;
}


Handle HandleManager::Add(void* data, u32 type)
{
	ASSERT(m_active_count < MAX_ENTRIES - 1);
	ASSERT(type >= 0 && type <= 31);

	const int new_index = m_first_free_entry;
	ASSERT(new_index < MAX_ENTRIES);
	ASSERT(m_entries[new_index].active == false);
	ASSERT(!m_entries[new_index].end);

	m_first_free_entry = m_entries[new_index].next_free_index;
	m_entries[new_index].next_free_index = 0;
	m_entries[new_index].counter = m_entries[new_index].counter + 1;
	if (m_entries[new_index].counter == 0)
	{
		m_entries[new_index].counter = 1;
	}
	m_entries[new_index].active = true;
	m_entries[new_index].data = data;

	++m_active_count;

	return Handle(new_index, m_entries[new_index].counter, type);
}


void HandleManager::Update(Handle handle, void* data)
{
	const int index = handle.index;
	ASSERT(m_entries[index].counter == handle.counter);
	ASSERT(m_entries[index].active == true);

	m_entries[index].data = data;
}


void HandleManager::Remove(const Handle handle)
{
	const u32 index = handle.index;
	ASSERT(m_entries[index].counter == handle.counter);
	ASSERT(m_entries[index].active == true);

	m_entries[index].next_free_index = m_first_free_entry;
	m_entries[index].active = 0;
	m_first_free_entry = index;

	m_active_count--;
}

void* HandleManager::Get(Handle handle) const
{
	void* data = nullptr;
	if (!Get(handle, data))
	{
		return nullptr;
	}
		
	return data;
}

bool HandleManager::Get(const Handle handle, void*& out) const
{
	const int index = handle.index;
	if (m_entries[index].counter != handle.counter || m_entries[index].active == false)
		return false;

	out = m_entries[index].data;

	return true;
}
