
import std;

using mask_t = unsigned char;
constexpr int mask_bit_count = sizeof(mask_t) * 8;

std::string alphabet = "eabcdfgh";

struct Cell
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

	inline int get_option_count()
	{
		return std::popcount(mask);
	}

	void print(std::string& alphabet)
	{
		int option_count = get_option_count();
		if (option_count == 1)
		{
			int number = std::countr_zero(mask);
			std::cout << alphabet[number];
		}
		else
		{
			std::cout << option_count;
		}
	}
};

struct Table
{
	int order;
	std::vector<Cell> cells;

	Table(int order)
		: order{ order }
	{
		mask_t init_mask = ~(~0 << order);
		cells.resize(order * order, init_mask);
	}

	Table(const Table& table)
		: order{ table.order }
		, cells{ table.cells }
	{
	}

	void print(std::string& alphabet)
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
				pCell->print(alphabet);
				pCell++;
			}
			std::cout << std::endl;
		}
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

void find_solutions(Table& table, std::vector<Table>& solutions)
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
			Table clone(table);
			clone.bind(cell_index, element_number);
			if (clone.is_valid())
			{
				find_solutions(clone, solutions);
			}
		}
	}
}

std::vector<Table> find_solutions(Table& table)
{
	std::vector<Table> solutions;
	find_solutions(table, solutions);
	return solutions;
}

std::vector<Table> find_normalized_latin_squares(int order)
{
	Table square(order);
	square.add_identity();
	return find_solutions(square);
}

int main()
{
	for (int order = 1; order <= 6; order++)
	{
		std::vector<Table> solutions = find_normalized_latin_squares(order);
		std::cout << solutions.size() << std::endl;
	}

	return 0;
}