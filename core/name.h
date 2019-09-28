#pragma once

#include "types.h"
#include "string.h"

class Name
{
public:
	Name() : m_id(0), m_index(0) {}
	Name(const char* string, bool unique = false);

	void Set(const char* string);
	
	bool operator == (const Name& other) const;
	bool operator != (const Name& other) const;
	bool operator  < (const Name& other) const;
	bool Compare(const Name& other) const;

	std::string string() const;
	const char* c_str() const;
	
	size_t GetID() const { return m_id; }

	static void InitializeNames();
	static void ShutdownNames();

private:
	size_t m_id;
	size_t m_index;
	static size_t ms_unique_id;

	static const size_t MAX_ENTRIES = 65536;
	static const size_t MAX_NAME_SIZE = 64;
	
	static char* ms_names;
};
