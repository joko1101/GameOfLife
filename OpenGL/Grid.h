#pragma once
#include <iostream>
#include <vector>
#include "Point.h"

class Grid
{
private:
	std::vector<std::vector<bool>> curr_gen;
	std::vector<std::vector<bool>> next_gen;
	int rand_factor, width, height, cell_size;

	void kill(int row, int col)
	{
		next_gen[row][col] = false;
	}

	void populate(int row, int col)
	{
		next_gen[row][col] = true;
	}

	void transfer(int row, int col)
	{
		next_gen[row][col] = curr_gen[row][col];
	}

	int getLiveNeighbours(int row, int col)
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
				if (n_row >= 0 && n_row < height-1 &&
					n_col >= 0 && n_col < width-1)
				{
					if (curr_gen[n_row][n_col])
						++live_neighbours;
				}
			}
		}
		return live_neighbours;
	}

public:
	Grid():rand_factor(5), width(100), height(100), cell_size(5) 
	{
		init();
	};

	Grid(int width, int height, int random_factor = 5, int cell_size = 5) : rand_factor(random_factor), width(width), height(height), cell_size(cell_size)
	{
		init();
	}

	void init()
	{
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

	void update()
	{
		// Next Generation
		if (next_gen.size() != 0)
		{
			next_gen.clear();
		}
		for (int row = 0; row < height-1; row++)
		{
			std::vector<bool> new_row;
			for (int col = 0; col < width-1; col++)
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

				/*next_gen[row][col] = curr_gen[row][col];
				if (next_gen[row][col] and
					(getLiveNeighbours(row, col) < 2 or getLiveNeighbours(row, col) > 3) or
					(!next_gen[row][col] and getLiveNeighbours(row, col) == 3))
				{
					next_gen[row][col] = !curr_gen[row][col];
				}*/

				/*if (next_gen[row][col] and 
					(getLiveNeighbours(row, col) < 2 or getLiveNeighbours(row, col) > 3))
				{
					kill(row, col);
				}
				else if (!next_gen[row][col] and getLiveNeighbours(row, col) == 3)
				{
					populate(row, col);
				}
				else 
				{
					transfer(row, col);
				}*/
			}
			next_gen.push_back(new_row);
		}
		curr_gen = next_gen;
		next_gen.clear();
	};

	void draw(RECT rc, HDC hdc)
	{
		for (int row = 0; row < height-1; row++)
		{
			for (int col = 0; col < width-1; col++)
			{
				if (curr_gen[row][col])
				{
					Point::draw(col * cell_size, row * cell_size, cell_size, rc, hdc, 0);
				}
			}
		}
	};
};