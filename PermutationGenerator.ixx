export module PermutationGenerator;

import std;
import Utils;
export import Permutation;

export class PermutationGenerator
{
public:
	std::vector<Permutation> get_permutation_list(int order)
	{
		std::vector<Permutation> result;

		int count = Utils::get_factorial(order);
		result.reserve(count);

		auto current = Permutation::CreateIdentity(order);
		result.push_back(current);
		while (current.next())
		{
			result.push_back(current);
		}

		return result;
	}
};