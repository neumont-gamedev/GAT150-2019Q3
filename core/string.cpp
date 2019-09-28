#include "string.h"
#include "assert.h"

#include "..\\external\crc\CRC.h"

#include <sstream>

void string_to_lower(const char* source, char* destination, size_t size)
{
	ASSERT_MSG(strlen(source) < size, "string size exceeds destination string buffer.");

	strcpy_s(destination, size, source);
	for (size_t i = 0; i < strlen(destination); ++i)
	{
		destination[i] = std::tolower(destination[i]);
	}
}

u32 string_to_hash(const char* string)
{
	return CRC::Calculate(string, strlen(string), CRC::CRC_32());
}

void tokenize(const std::string& string, char delimiter, std::vector<std::string>& strings)
{
	std::stringstream stream(string);
	std::string s;

	while (std::getline(stream, s, delimiter))
	{
		strings.push_back(s);
	}
}

bool compare_char(char& c1, char& c2)
{
	return ((c1 == c2) || std::toupper(c1) == std::toupper(c2));
}

bool string_compare_no_case(std::string& string1, std::string& string2)
{
	return ((string1.size() == string2.size()) &&
		std::equal(string1.begin(), string1.end(), string2.begin(), &compare_char));
}
