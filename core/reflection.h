#pragma once

#define REFLECT_ENUM(data) {#data, data}

template <typename T>
struct property_t
{
	const char* name;
	T data;
};

template<typename T>
bit_mask_t CreateBitMask(T* property, size_t size, std::vector<std::string>& tokens)
{
	bit_mask_t bits;

	for (std::string& string : tokens)
	{
		for (size_t i = 0; i < size; i++)
		{
			std::string state_string(property[i].name);
			if (string_compare_no_case(string, state_string))
			{
				bits.set(property[i].data);
			}
		}
	}

	return bits;
}
