#include "json.h"
#include "filesystem.h"
#include <iostream>

bool json::load(const char* filename, rapidjson::Document& document)
{
	bool success = false;

	char* buffer;
	size_t size;

	if (filesystem::read_file(filename, (void**)& buffer, size))
	{
		buffer[size - 1] = 0;
		std::cout << buffer;
		document.Parse(buffer);
		success = document.IsObject();

		filesystem::free_file(buffer);
	}

	return success;
}

bool json::get_int(const rapidjson::Value& value, const char* property_name, int& _int)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsInt() == false)
	{
		return false;
	}

	_int = property.GetInt();

	return true;
}

bool json::get_float(const rapidjson::Value& value, const char* property_name, float& _float)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsDouble() == false)
	{
		return false;
	}

	_float = property.GetFloat();

	return true;
}

bool json::get_string(const rapidjson::Value& value, const char* property_name, std::string& string)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsString() == false)
	{
		return false;
	}

	string = property.GetString();

	return true;
}

bool json::get_strings(const rapidjson::Value& value, const char* property_name, char delimiter, std::vector<std::string>& strings)
{
	std::string string;
	get_string(value, property_name, string);

	tokenize(string, delimiter, strings);

	return true;
}

bool json::get_bool(const rapidjson::Value& value, const char* property_name, bool& _bool)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsBool() == false)
	{
		return false;
	}

	_bool = property.GetBool();

	return true;
}

bool json::get_vector2(const rapidjson::Value& value, const char* property_name, vector2& _vector2)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsArray() == false || property.Size() != 2)
	{
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 2; i++)
	{
		if (property[i].IsDouble() == false)
		{
			return false;
		}
	}

	_vector2.x = property[0].GetFloat();
	_vector2.y = property[1].GetFloat();

	return true;
}

bool json::get_vector2(const rapidjson::Value& value, const char* property_name, std::vector<vector2>& _vector2)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++)
	{
		const rapidjson::Value& vertex = value[i];
		if (vertex.IsObject())
		{
			vector2 v2;
			get_vector2(vertex, property_name, v2);
			_vector2.push_back(v2);
		}
	}

	return true;
}

bool json::get_color(const rapidjson::Value& value, const char* property_name, color& _color)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsArray() == false || property.Size() != 3)
	{
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 3; i++)
	{
		if (property[i].IsDouble() == false)
		{
			return false;
		}
	}

	_color.r = property[0].GetFloat();
	_color.g = property[1].GetFloat();
	_color.b = property[2].GetFloat();

	return true;
}

bool json::get_color(const rapidjson::Value& value, const char* property_name, std::vector<color>& colors)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++)
	{
		const rapidjson::Value& color_value = value[i];
		if (color_value.IsObject())
		{
			color c;
			get_color(color_value, property_name, c);
			colors.push_back(c);
		}
	}

	return true;
}

bool json::get_name(const rapidjson::Value& value, const char* property_name, Name& name)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsString() == false)
	{
		return false;
	}

	name = property.GetString();

	return true;
}
