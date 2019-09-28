#pragma once
#include "handle.h"

class HandleManager
{
public:
	enum { MAX_ENTRIES = 4096 }; // 2^12

	HandleManager();
	HandleManager(const HandleManager&) = delete;
	HandleManager& operator=(const HandleManager&) = delete;

	void Reset();
	Handle Add(void* p, u32 type = 0);
	void Update(Handle handle, void* p);
	void Remove(Handle handle);

	void* Get(Handle handle) const;
	bool Get(Handle handle, void*& out) const;
	template< typename T > bool Get(Handle handle, T& out) const;

	int GetCount() const { return m_active_count; }

private:
	struct HandleEntry
	{
		HandleEntry() : next_free_index(0), counter(1), active(0), end(0), data(NULL) {}
		explicit HandleEntry(u32 next_free_index) : next_free_index(next_free_index), counter(1), active(0), end(0), data(NULL) {}

		u32 next_free_index : 12;
		u32 counter			: 15;
		u32 active			: 1;
		u32 end				: 1;
		void* data;
	};

	HandleEntry m_entries[MAX_ENTRIES];

	int m_active_count;
	u32 m_first_free_entry;
};

template< typename T >
inline bool HandleManager::Get(Handle handle, T& out) const
{
	void* data;
	const bool result = Get(handle, data);
	out = reinterpret_cast<T>(data);

	return result;
}
