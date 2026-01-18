export module SquareTable;

import std;

export struct RowCol
{
	int row;
	int col;
};

export template <typename CellT>
struct SquareTable
{
	int order;
	std::vector<CellT> cells;

	SquareTable(int order)
		: order{ order }
		, cells( order * order )
	{
	}

	SquareTable(int order, const std::vector<CellT>& cells)
		: order{ order }
		, cells{ cells }
	{
	}

	CellT& operator[](RowCol multiindex)
	{
		return cells[multiindex.row * order + multiindex.col];
	}

	CellT& get_cell(RowCol multiindex)
	{
		return cells[multiindex.row * order + multiindex.col];
	}

	const CellT& get_cell(RowCol multiindex) const
	{
		return cells[multiindex.row * order + multiindex.col];
	}
};