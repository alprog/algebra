
import std;

import CayleyTable;
import TableGenerator;
import PermutationGenerator;

std::string alphabet = "eabcdfgh";

int main()
{
	TableGenerator generator;

	for (int order = 1; order <= 5; order++)
	{
		std::vector<CayleyTable> tables = generator.find_latin_squares(order, true);
		std::cout << tables.size() << std::endl;

		auto permutation_list = PermutationGenerator().get_permutation_list(order);
		std::cout << permutation_list.size() << std::endl;
	}

	return 0;
}