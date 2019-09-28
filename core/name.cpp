#include "name.h"
#include "assert.h"
#include "..\\external\crc\CRC.h"

char* Name::ms_names = nullptr;
size_t Name::ms_unique_id = 0;

void Name::InitializeNames()
{
	ms_names = new char[MAX_ENTRIES * MAX_NAME_SIZE];
}

void Name::ShutdownNames()
{
	delete ms_names;
}

Name::Name(const char* string, bool unique)
{
	if (unique)
	{
		std::string unique_string(string);
		unique_string += std::to_string(ms_unique_id);
		Set(unique_string.c_str());
		ms_unique_id++;
	}
	else
	{
		Set(string);
	}
}

void Name::Set(const char* string)
{
	ASSERT(strlen(string) < MAX_NAME_SIZE);

	char string_lower[MAX_NAME_SIZE];
	string_to_lower(string, string_lower, MAX_NAME_SIZE);

	m_id = std::hash<std::string>{}(string_lower);
	m_index = m_id % MAX_ENTRIES;

	strcpy_s(ms_names + (m_index * MAX_NAME_SIZE), MAX_NAME_SIZE, string);
}

bool Name::operator==(const Name& other) const
{
	return m_id == other.m_id;
}

bool Name::operator!=(const Name& other) const
{
	return m_id != other.m_id;
}

bool Name::operator<(const Name& other) const
{
	return m_id < other.m_id;
}

bool Name::Compare(const Name& other) const
{
	return m_id == other.m_id;
}

std::string Name::string() const
{
	std::string string(c_str());
	return string;
}

const char* Name::c_str() const
{
	return ms_names + (m_index * MAX_NAME_SIZE);
}


