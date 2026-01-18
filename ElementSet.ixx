export module ElementSet;

import std;
export import ElementIndex;

export struct ElementSet
{
	using mask_t = unsigned char;
	static constexpr int mask_bit_count = sizeof(mask_t) * 8;

	mask_t mask = 0xFF;

	ElementSet(mask_t mask)
		: mask{ mask }
	{
	}

	void assign_element(int element_number)
	{
		mask = 1 << element_number;
	}

	inline bool has_options()
	{
		return mask != 0;
	}

	inline bool is_element_allowed(int element_number)
	{
		return mask & (1 << element_number);
	}

	void unset(int exclude_mask)
	{
		mask = mask & ~exclude_mask;
	}

	inline int get_option_count() const
	{
		return std::popcount(mask);
	}

	inline ElementIndex get_element_index() const
	{
		return std::countr_zero(mask);
	}

	void print(const std::string& alphabet)
	{
		int option_count = get_option_count();
		if (option_count == 1)
		{
			int number = std::countr_zero(mask);
			std::cout << alphabet[number];
		}
		else
		{
			std::cout << option_count;
		}
	}

	auto operator<=>(const ElementSet& other) const = default;
};