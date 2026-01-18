export module PermutationGenerator;

import std;
import Utils;
import PermutationCache;

export class PermutationGenerator
{
public:
	static std::vector<Permutation> create_permutation_list(int order)
	{
		std::vector<Permutation> result;
		result.reserve(Utils::get_factorial(order));

		auto current = Permutation::CreateIdentity(order);
		result.push_back(current);
		while (current.next())
		{
			result.push_back(current);
		}

		return result;
	}

	static std::vector<Permutation> create_permutation_list_with_fixed_identity(int order)
	{
		const auto& tail_permutations = get_permutation_list(order - 1, false);

		std::vector<Permutation> result;
		result.reserve(tail_permutations.size());

		for (const auto& tail_perm : tail_permutations)
		{
			Permutation& perm = result.emplace_back();
			perm.mapping.resize(order);
			perm.mapping[0] = 0;
			for (int i = 1; i < order; ++i)
			{
				perm.mapping[i] = tail_perm.mapping[i - 1] + 1;
			}
		}

		return result;
	}

	static const std::vector<Permutation>& get_permutation_list(int order, bool fixed_identity)
	{
		if (fixed_identity)
		{
			static PermutationCache cache(create_permutation_list_with_fixed_identity);
			return cache.get_list(order);
		}
		else
		{
			static PermutationCache cache(create_permutation_list);
			return cache.get_list(order);
		}
	}

	static const Permutation& get_identity_transposition(int order, ElementIndex index)
	{
		using TKey = std::pair<int, ElementIndex>;
		static std::map<TKey, Permutation> cache;

		TKey key { order, index };
		auto it = cache.find(key);
		if (it != cache.end())
		{
			return it->second;
		}

		auto perm = Permutation::CreateIdentity(order);
		std::swap(perm.mapping[0], perm.mapping[index]);
		cache[key] = perm;
		return cache[key];
	}
};