export module PermutationCache;

import std;

export import Permutation;

export struct PermutationCache
{
	using CreationCallback = std::function<std::vector<Permutation>(int)>;

	std::vector<std::vector<Permutation>> cache;
	CreationCallback creation_callback;

	PermutationCache(const CreationCallback& callback)
		: creation_callback{ callback }
	{
	}

	const std::vector<Permutation>& get_list(int order)
	{
		if (order >= cache.size())
		{
			cache.resize(order + 1);
		}
		auto& cached_list = cache[order];
		if (cached_list.empty())
		{
			cached_list = creation_callback(order);
		}
		return cached_list;
	}
};