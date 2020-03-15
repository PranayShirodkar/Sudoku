// Library Includes
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>

// Project Includes
#include "Sudoku.hpp"
#include "SudokuGenerator.hpp"

SudokuGenerator::SudokuGenerator()
{
	srand(int(time(NULL)));
	GenerateRandomGrid();
}
SudokuGenerator::~SudokuGenerator()
{
}

std::vector<std::vector<int>> SudokuGenerator::GetPuzzle()
{
	return sudokuGrid;
}

void SudokuGenerator::GenerateRandomGrid()
{
	// Case 1: rearrange the columns
	// Every 3 columns can be rearranged among themselves
	// Every block of 3 columns can be rearranged among themselves
	// This form of scrambling preserves sudoku solvability
	std::vector<std::vector<int>> tempGrid(9, std::vector<int>(9, 0));
	std::vector<int> randomArray = GenerateRandomRowColArray();

	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			tempGrid[i][j] = sudokuGrid[i][randomArray[j]];
		}
	}
	sudokuGrid = tempGrid;

	// Case 2: rearrange the rows
	// Every 3 rows can be rearranged among themselves
	// Every block of 3 rows can be rearranged among themselves
	// This form of scrambling preserves sudoku solvability
	tempGrid = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
	randomArray = GenerateRandomRowColArray();

	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			tempGrid[i][j] = sudokuGrid[randomArray[i]][j];
		}
	}
	sudokuGrid = tempGrid;

	// Case 3: scramble the numbers such that all ones become threes, all threes become eights, etc.
	// This form of scrambling preserves sudoku solvability
	tempGrid = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
	randomArray = GenerateRandomArray();

	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			if (sudokuGrid[i][j] != 0)
			{
				tempGrid[i][j] = randomArray[sudokuGrid[i][j]-1]+1;
			}
		}
	}
	sudokuGrid = tempGrid;
}

std::vector<int> SudokuGenerator::GenerateRandomArray()
{
	// generate randomArray of 0-8 scrambled
	std::vector<int> randomArray;
	for (int x = 0; x < NUM_OF_COLUMNS; x++)
	{
		randomArray.push_back(x);
	}
	random_shuffle(randomArray.begin(), randomArray.end());
	return randomArray;
}

std::vector<int> SudokuGenerator::GenerateRandomRowColArray()
{
	// This method does the following:
	// tempArray = [[0,1,2],
	//              [3,4,5],
	//              [6,7,8]]
	// shuffle the subarrays in tempArray
	// shuffle the contents of each subarray in tempArray
	// populate tempArray into randomArray, for example:
	// 8,7,6,1,0,2,4,3,5  or  5,3,4,6,8,7,0,2,1
	std::vector<int> randomArray;
	std::vector<std::vector<int>> tempArray(3, std::vector<int>(3, 0));
	std::vector<std::vector<int>>::iterator it;
	int i = 0;
	for (uint32_t x = 0; x < tempArray.size(); x++)
	{
		for (uint32_t y = 0; y < tempArray.size(); y++)
		{
			tempArray[x][y] = i;
			i++;
		}
	}

	random_shuffle(tempArray.begin(), tempArray.end());
	for (it = tempArray.begin(); it != tempArray.end(); it++)
	{
		random_shuffle(it->begin(), it->end());
		randomArray.insert(randomArray.end(), it->begin(), it->end());
	}
	return randomArray;
}