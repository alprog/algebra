export module CayleyTable;

import std;
export import ElementIndex;
export import SquareTable;

export struct CayleyTable : public SquareTable<ElementIndex>
{
	using Base = SquareTable<ElementIndex>;
	
	using Base::SquareTable;

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
};