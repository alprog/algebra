export module CayleyTable;

import std;
export import ElementIndex;
export import SquareTable;
export import Permutation;
export import PermutationGenerator;

export struct CayleyTable : public SquareTable<ElementIndex>
{
	using Base = SquareTable<ElementIndex>;

	using Base::SquareTable;

	ElementIndex find_identity_element() const
	{
		for (int i = 0; i < order; ++i)
		{
			if (is_identity_element(i))
			{
				return i;
			}
		}
		return -1;
	}

	bool is_identity_element(ElementIndex index) const
	{
		for (int i = 0; i < order; ++i)
		{
			if (get_cell({ index, i }) != i || get_cell({ i, index }) != i)
			{
				return false;
			}
		}
		return true;
	}

	void print(const std::string& alphabet) const
	{
		std::cout << ". |";
		for (int i = 0; i < order; ++i)
		{
			std::cout << ' ' << alphabet[i];
		}
		std::cout << std::endl;
		std::cout << "--|" << std::string(order * 2, '-') << std::endl;

		auto* pCell = &cells[0];
		for (int r = 0; r < order; ++r)
		{
			std::cout << alphabet[r] << " |";
			for (int c = 0; c < order; ++c)
			{
				std::cout << ' ' << alphabet[*pCell++];
			}
			std::cout << std::endl;
		}
	}

	CayleyTable get_isomorphic_table(const Permutation& element_order_permutation) const
	{
		CayleyTable result(order);
		for (int r = 0; r < order; ++r)
		{
			for (int c = 0; c < order; ++c)
			{
				int new_r = element_order_permutation.mapping[r];
				int new_c = element_order_permutation.mapping[c];
				int original_value = get_cell({ r, c });
				int new_value = element_order_permutation.mapping[original_value];
				result.get_cell({ new_r, new_c }) = new_value;
			}
		}
		return result;
	}

	CayleyTable get_normalized_table() const
	{
		ElementIndex identity_index = find_identity_element();
		if (identity_index == 0 || identity_index == 255)
		{
			return *this; // already normalized or can't be normalized
		}

		auto& transposition = PermutationGenerator::get_identity_transposition(order, identity_index);
		return get_isomorphic_table(transposition);
	}

	std::partial_ordering operator<=>(const CayleyTable& rhs) const
	{
		return cells <=> rhs.cells;
	}
};