export module LatinSquare;

import std;

import CayleyTable;

using mask_t = unsigned char;
constexpr int mask_bit_count = sizeof(mask_t) * 8;

export struct Cell
{
	mask_t mask = 0xFF;

	Cell(mask_t mask)
		: mask{ mask }
	{
	}

	void assign(int element_number)
	{
		mask = 1 << element_number;
	}

	inline bool has_options()
	{
		return mask != 0;
	}

	inline bool is_element_allowed(int element_number)
	{
		return mask & (1 << element_number);
	}

	void unset(int exclude_mask)
	{
		mask = mask & ~exclude_mask;
	}

	inline int get_option_count() const
	{
		return std::popcount(mask);
	}

	auto operator<=>(const Cell& other) const = default;
};

template <>
void print<Cell>(const Cell& cell, const std::string& alphabet)
{
	int option_count = cell.get_option_count();
	if (option_count == 1)
	{
		int number = std::countr_zero(cell.mask);
		std::cout << alphabet[number];
	}
	else
	{
		std::cout << option_count;
	}
}

export struct LatinSquare : public CayleyTable<Cell>
{
	using Base = CayleyTable<Cell>;

	LatinSquare(int order)
		: Base{ order }
	{
		mask_t init_mask = ~(~0 << order);
		cells.resize(order * order, init_mask);
	}

	LatinSquare(const LatinSquare& table)
		: Base{ table.order, table.cells }
	{
	}

	void bind(int cell_index, int element_number)
	{
		int row = cell_index / order;
		int col = cell_index % order;
		bind(row, col, element_number);
	}

	void bind(int row, int col, int element_number)
	{
		cells[index(row, col)].assign(element_number);
		cross_exclude_from_neighbors(row, col);
	}

	void cross_exclude_from_neighbors(int row, int col)
	{
		mask_t exclude_mask = cells[index(row, col)].mask;
		for (int i = 0; i < order; i++)
		{
			if (i != row)
			{
				exclude_from_cell(i, col, exclude_mask);
			}
			if (i != col)
			{
				exclude_from_cell(row, i, exclude_mask);
			}
		}
	}

	void exclude_from_cell(int row, int col, mask_t exclude_mask)
	{
		Cell& cell = cells[index(row, col)];
		if (cell.mask & exclude_mask)
		{
			cell.unset(exclude_mask);
			if (cell.get_option_count() == 1)
			{
				cross_exclude_from_neighbors(row, col);
			}
		}
	}

	void add_identity()
	{
		for (int i = 0; i < order; i++)
		{
			bind(0, i, i);
			bind(i, 0, i);
		}
	}

	int get_index(Cell* pCell)
	{
		return pCell - &cells[0];
	}

	int index(int r, int c)
	{
		return r * order + c;
	}

	Cell* find_least_ambiguous_cell()
	{
		Cell* best_cell = nullptr;
		int min_option_count = std::numeric_limits<int>::max();

		for (auto& cell : cells)
		{
			int option_count = cell.get_option_count();
			if (option_count == 2)
			{
				return &cell;
			}
			else if (option_count > 1 && option_count < min_option_count)
			{
				best_cell = &cell;
				min_option_count = option_count;
			}
		}

		return best_cell;
	}

	bool is_valid()
	{
		for (auto& cell : cells)
		{
			if (!cell.has_options())
			{
				return false;
			}
		}
		return true;
	}
};