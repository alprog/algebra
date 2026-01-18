export module TableGenerator;

import std;

import CayleyTable;
import IncompleteLatinSquare;
import PermutationGenerator;

export using IsomorphicCollection = std::set<CayleyTable>;

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

	std::vector<IsomorphicCollection> make_isomorphic_collections(const std::vector<CayleyTable>& tables)
	{
		std::vector<IsomorphicCollection> collections;

		std::set<CayleyTable> unique_set;
		for (const CayleyTable& table : tables)
		{
			if (unique_set.contains(table))
			{
				continue;
			}

			auto norm_table = table.get_normalized_table();
			if (unique_set.contains(norm_table))
			{
				continue;
			}

			auto collection = create_isomorphic_collection(norm_table);
			collections.push_back(collection);
			collections.back();
			unique_set.insert(collection.begin(), collection.end());
		}

		return collections;
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

	IsomorphicCollection create_isomorphic_collection(const CayleyTable& table)
	{
		IsomorphicCollection collection = { table };

		const bool fixed_identity = table.is_identity_element(0);
		const auto& permutations = PermutationGenerator::get_permutation_list(table.order, fixed_identity);

		for (int i = 1; i < permutations.size(); i++) // skip identity permutation at index 0
		{
			const Permutation& permutation = permutations[i];
			collection.insert(table.get_isomorphic_table(permutation));
		}

		return collection;
	}
};