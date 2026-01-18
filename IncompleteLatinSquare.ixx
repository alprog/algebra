export module IncompleteLatinSquare;

import std;

export import ElementSet;
export import SquareTable;
export import CayleyTable;

// for intellisense

export struct IncompleteLatinSquare : public SquareTable<ElementSet>
{
	using Base = SquareTable<ElementSet>;
	using CellT = ElementSet;

	IncompleteLatinSquare(int order)
		: Base{ order }
	{
		ElementSet::mask_t init_mask = ~(~0 << order);
		cells.resize(order * order, init_mask);
	}

	IncompleteLatinSquare(const IncompleteLatinSquare& table)
		: Base{ table.order, table.cells }
	{
	}

	void bind(int cell_index, int element_number)
	{
		int row = cell_index / order;
		int col = cell_index % order;
		bind({ row, col }, element_number);
	}

	void bind(RowCol pos, int element_number)
	{
		get_cell(pos).assign_element(element_number);
		cross_exclude_from_neighbors(pos);
	}

	void cross_exclude_from_neighbors(RowCol pos)
	{
		auto exclude_mask = get_cell(pos).mask;
		for (int i = 0; i < order; i++)
		{
			if (i != pos.row)
			{
				exclude_from_cell({ i, pos.col }, exclude_mask);
			}
			if (i != pos.col)
			{
				exclude_from_cell({ pos.row, i }, exclude_mask);
			}
		}
	}

	void exclude_from_cell(RowCol pos, ElementSet::mask_t exclude_mask)
	{
		CellT& cell = get_cell(pos);
		if (cell.mask & exclude_mask)
		{
			cell.unset(exclude_mask);
			if (cell.get_option_count() == 1)
			{
				cross_exclude_from_neighbors(pos);
			}
		}
	}

	void normalize()
	{
		for (int i = 0; i < order; i++)
		{
			bind({ 0, i }, i);
			bind({ i, 0 }, i);
		}
	}

	int get_index(CellT* pCell)
	{
		return pCell - &cells[0];
	}

	int index(int r, int c)
	{
		return r * order + c;
	}

	CellT* find_least_ambiguous_cell()
	{
		CellT* best_cell = nullptr;
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

	CayleyTable to_cayley_table()
	{
		std::vector<ElementIndex> elements(cells.size());
		std::transform(cells.begin(), cells.end(), elements.begin(), [](ElementSet x) { return x.get_element_index(); });

		return CayleyTable(order, elements);
	}

	void print(const std::string& alphabet)
	{
		auto* pCell = &cells[0];
		for (int r = 0; r < order; ++r)
		{
			for (int c = 0; c < order; ++c)
			{
				pCell->print(alphabet);
				std::cout << ' ';
				pCell++;
			}
			std::cout << std::endl;
		}
	}
};