
import std;

import CayleyTable;
import TableGenerator;

std::string alphabet = "eabcdfgh";

int main()
{
	TableGenerator generator;

	for (int order = 1; order <= 6; order++)
	{
		std::vector<CayleyTable> tables = generator.find_latin_squares(order, true);
		std::cout << tables.size() << std::endl;
	}

	return 0;
}