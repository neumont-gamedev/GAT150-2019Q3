#pragma once

#include "types.h"
#include <string>
#include <vector>

void string_to_lower(const char* source, char* destination, size_t size);
u32  string_to_hash(const char* string);
void tokenize(const std::string& string, char delimiter, std::vector<std::string>& strings);
bool string_compare_no_case(std::string& string1, std::string& string2);
