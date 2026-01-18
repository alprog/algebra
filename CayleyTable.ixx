export module CayleyTable;

import std;
export import ElementIndex;
export import SquareTable;
export import Permutation;

export struct CayleyTable : public SquareTable<ElementIndex>
{
	using Base = SquareTable<ElementIndex>;
	
	using Base::SquareTable;

	bool is_first_element_identity()
	{
		for (int i = 0; i < order; ++i)
		{
			if (get_cell({ 0, i }) != i || get_cell({ i, 0 }) != i)
			{
				return false;
			}
		}
		return true;
	}

	void print(const std::string& alphabet)
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

	CayleyTable get_isomorphic_table(const Permutation& element_order_permutation)
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
};