export module TableGenerator;

import std;

import CayleyTable;
import IncompleteLatinSquare;

using IsomorphicCollection = std::vector<CayleyTable>;

export class TableGenerator
{
public:
	std::vector<CayleyTable> find_latin_squares(int order, bool normalized)
	{
		IncompleteLatinSquare square(order);
		if (normalized)
		{
			square.normalize();
		}
		std::vector<CayleyTable> solutions;
		find_solutions_recursive(square, solutions);
		return solutions;
	}

	std::vector<IsomorphicCollection> combine_isomorphic(const std::vector<CayleyTable>& tables)
	{
		std::vector<IsomorphicCollection> collections;

		std::set<std::vector<ElementIndex>> unique_set;
		for (const CayleyTable& table : tables)
		{
			if (!unique_set.contains(table.cells))
			{
				collections.push_back(create_isomorphic_collection(table));
				for (const auto& table : collections.back())
				{
					unique_set.insert(table.cells);
				}
			}
		}

		return collections;
	}

	IsomorphicCollection create_isomorphic_collection(const CayleyTable& table)
	{
		IsomorphicCollection collection = { table };

		return collection;
	}

private:
	void find_solutions_recursive(IncompleteLatinSquare& square, std::vector<CayleyTable>& solutions)
	{
		auto* ambiguous_cell = square.find_least_ambiguous_cell();
		if (ambiguous_cell == nullptr)
		{
			solutions.push_back(square.to_cayley_table()); // completed square
			return;
		}

		int cell_index = square.get_index(ambiguous_cell);
		for (int element_number = 0; element_number < square.order; element_number++)
		{
			if (ambiguous_cell->is_element_allowed(element_number))
			{
				IncompleteLatinSquare clone(square);
				clone.bind(cell_index, element_number);
				if (clone.is_valid())
				{
					find_solutions_recursive(clone, solutions);
				}
			}
		}
	}

};