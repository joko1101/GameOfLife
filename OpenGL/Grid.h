#pragma once
#include "Point.h"

class Grid
{
private:
	std::vector<std::vector<bool>> curr_gen;
	std::vector<std::vector<bool>> next_gen;
	int rand_factor, width, height, cell_size;

	void kill(int row, int col);

	void populate(int row, int col);

	void transfer(int row, int col);

	int getLiveNeighbours(int row, int col);

public:
	Grid();

	Grid(
		int width, 
		int height, 
		int random_factor, 
		int cell_size);

	void init();

	void update();

	void draw();
};