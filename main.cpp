
import std;

import CayleyTable;
import TableGenerator;

std::string alphabet = "eabcdfgh";

int main()
{
	TableGenerator generator;

	for (int order = 1; order <= 5; order++)
	{
		std::cout << "Order: " << order << std::endl;

		std::vector<CayleyTable> tables = generator.find_latin_squares(order, true);
		std::cout << "Latin squares: " << tables.size() << std::endl;

		std::vector<IsomorphicCollection> collections = generator.make_isomorphic_collections(tables);

		std::cout << "Not isomorphic: " << collections.size() << std::endl;
		
		for (auto& collection : collections)
		{
			const CayleyTable& table = *collection.begin();
			table.print(alphabet);
			std::cout << (int)table.find_identity_element() << std::endl;
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	return 0;
}