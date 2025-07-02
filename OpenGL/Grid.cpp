#include "Grid.h"
#include "GraphicsController.h"

// ---------------------------------- PRIVATE ---------------------------------- \\

void Grid::kill(int row, int col)
{
	next_gen[row][col] = false;
}

void Grid::populate(int row, int col)
{
	next_gen[row][col] = true;
}

void Grid::transfer(int row, int col)
{
	next_gen[row][col] = curr_gen[row][col];
}

int Grid::getLiveNeighbours(int row, int col)
{
	int live_neighbours = 0;
	for (int dr = -1; dr <= 1; ++dr)
	{
		for (int dc = -1; dc <= 1; ++dc)
		{
			if (dr == 0 && dc == 0)
				continue; // Skip the cell itself
			int n_row = row + dr;
			int n_col = col + dc;
			// Check bounds
			if (n_row >= 0 && n_row < height &&
				n_col >= 0 && n_col < width)
			{
				if (curr_gen[n_row][n_col])
					++live_neighbours;
			}
		}
	}
	return live_neighbours;
}

// ---------------------------------- PUBLIC ---------------------------------- \\

Grid::Grid()
	: rand_factor(10)
	, cell_size(10)
	, width(Metadata::getInstance()->getWndWidth() / cell_size)
	, height(Metadata::getInstance()->getWndHeight() / cell_size)
{
	init();
};

Grid::Grid(int width, int height, int random_factor = 10, int cell_size = 10)
	: rand_factor(random_factor)
	, width(width / cell_size)
	, height(height / cell_size)
	, cell_size(cell_size)
{
	init();
}

void Grid::init()
{
	srand((unsigned int)time(nullptr) * rand());

	for (int row = 0; row < height; row++)
	{
		std::vector<bool> new_row;
		for (int col = 0; col < width; col++)
		{
			if (col == 0
				or col == width - 1
				or row == 0
				or row == height - 1)
			{
				new_row.push_back(false); // border
			}
			else
			{
				if (rand() % rand_factor == 0)
				{
					new_row.push_back(true);
				}
				else
				{
					new_row.push_back(false);
				}
			}
		}
		curr_gen.push_back(new_row);
	}
}

void Grid::update()
{
	// Next Generation
	if (next_gen.size() != 0)
	{
		next_gen.clear();
	}
	for (int row = 0; row < height; row++)
	{
		std::vector<bool> new_row;
		for (int col = 0; col < width; col++)
		{
			if (col == 0
				or col == width - 1
				or row == 0
				or row == height - 1)
			{
				new_row.push_back(false); // border
			}
			else
			{
				new_row.push_back(curr_gen[row][col]);
				if (curr_gen[row][col] and
					(getLiveNeighbours(row, col) < 2 or getLiveNeighbours(row, col) > 3) or
					(!curr_gen[row][col] and getLiveNeighbours(row, col) == 3))
				{
					new_row.at(new_row.size() - 1) = !new_row.at(new_row.size() - 1);
				}
			}
		}
		next_gen.push_back(new_row);
	}
	curr_gen = next_gen;
	next_gen.clear();
};

void Grid::draw()
{
	GraphicsController::getShader("simple")->use();

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (col == 0
				or row == 0
				or col == width - 1
				or row == height - 1)
			{
				int x = col * cell_size - width * cell_size / 2;
				int y = row * cell_size - height * cell_size / 2;

				Point(x, y, cell_size, 255, 255, 255).draw();
			}
			if (curr_gen[row][col])
			{
				int x = col * cell_size - width * cell_size / 2;
				int y = row * cell_size - height * cell_size / 2;
				Point(x, y, cell_size, 255, 255, 255).draw();
			}
		}
	}
};
