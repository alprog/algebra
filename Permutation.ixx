export module Permutation;

import std;
export import ElementIndex;

export struct Permutation
{
	std::vector<ElementIndex> mapping;

	static Permutation CreateIdentity(int order)
	{
		Permutation result;
		result.mapping.resize(order);
		for (int i = 0; i < order; ++i)
		{
			result.mapping[i] = static_cast<ElementIndex>(i);
		}
		return result;
	}

	bool next()
	{
		return std::next_permutation(mapping.begin(), mapping.end());
	}
};