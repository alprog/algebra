
import std;

import LatinSquare;

std::string alphabet = "eabcdfgh";



void find_solutions(LatinSquare& table, std::vector<LatinSquare>& solutions)
{
	Cell* ambiguous_cell = table.find_least_ambiguous_cell();
	if (ambiguous_cell == nullptr)
	{
		solutions.push_back(table);

		//if (solutions.size() % 100000 == 0)
		//{
		//	std::cout << solutions.size() << std::endl;
		//}

		return;
	}

	int cell_index = table.get_index(ambiguous_cell);
	for (int element_number = 0; element_number < table.order; element_number++)
	{
		if (ambiguous_cell->is_element_allowed(element_number))
		{
			LatinSquare clone(table);
			clone.bind(cell_index, element_number);
			if (clone.is_valid())
			{
				find_solutions(clone, solutions);
			}
		}
	}
}

std::vector<LatinSquare> find_solutions(LatinSquare& table)
{
	std::vector<LatinSquare> solutions;
	find_solutions(table, solutions);
	return solutions;
}

std::vector<LatinSquare> find_normalized_latin_squares(int order)
{
	LatinSquare square(order);
	square.add_identity();
	square.print(alphabet);
	return find_solutions(square);
}

int main()
{
	LatinSquare t(4);
	LatinSquare tt(4);
	auto c = t.cells == t.cells;

	std::map<std::vector<Cell>, int> m;
	m[t.cells] = 3;


	for (int order = 1; order <= 6; order++)
	{
		std::vector<LatinSquare> solutions = find_normalized_latin_squares(order);
		std::cout << solutions.size() << std::endl;
	}

	return 0;
}