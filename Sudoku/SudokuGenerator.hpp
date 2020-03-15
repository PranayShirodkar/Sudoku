#pragma once

// Library Includes
#include <vector>

class SudokuGenerator
{
public:
	SudokuGenerator();
	~SudokuGenerator();
	std::vector<std::vector<int>> GetPuzzle();
	void GenerateRandomGrid();
	std::vector<int> GenerateRandomArray();
	std::vector<int> GenerateRandomRowColArray();

private:
	std::vector<std::vector<int>> sudokuGrid =  {
												{7,8,0,4,0,0,1,2,0},
												{6,0,0,0,7,5,0,0,9},
												{0,0,0,6,0,1,0,7,8},
												{0,0,7,0,4,0,2,6,0},
												{0,0,1,0,5,0,9,3,0},
												{0,0,4,0,6,0,0,0,5},
												{0,7,0,3,0,0,0,1,2},
												{1,2,0,0,0,7,4,0,0},
												{0,4,9,2,0,6,0,0,7}
												};
	//std::vector<std::vector<int>> sudokuGrid =  {
	//											{2,9,5,7,4,3,8,6,1},
	//											{4,3,1,8,6,5,9,0,0},
	//											{8,7,6,1,9,2,5,4,3},
	//											{3,8,7,4,5,9,2,1,6},
	//											{6,1,2,3,8,7,4,9,5},
	//											{5,4,9,2,1,6,7,3,8},
	//											{7,6,3,5,2,4,1,8,9},
	//											{9,2,8,6,7,1,3,5,4},
	//											{1,5,4,9,3,8,6,0,0}
	//											};
};

