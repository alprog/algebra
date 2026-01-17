export module CayleyTable;

import std;

using ElementIndex = unsigned char;

export template <typename T>
void print(const T& value, const std::string& alphabet);

export template <ElementIndex>
void print(const ElementIndex& element_index, const std::string& alphabet)
{
	std::cout << alphabet[element_index];
}

export template <typename CellT>
struct CayleyTable
{
	int order;
	std::vector<CellT> cells;

	CayleyTable(int order)
		: order{ order }
		, cells{ order * order }
	{
	}

	CayleyTable(int order, std::vector<CellT> cells)
		: order{ order }
		, cells{ cells }
	{
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
				std::cout << ' ';
				::print(*pCell, alphabet);
				pCell++;
			}
			std::cout << std::endl;
		}
	}
};