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
	// Setup before Case 1
	std::vector<std::vector<int>> tempGrid(9, std::vector<int>(9, 0));
	std::vector<int> randomArray = GenerateRandomRowColArray();

	// Case 1: rearrange the columns
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			tempGrid[i][j] = sudokuGrid[i][randomArray[j]];
		}
	}
	sudokuGrid = tempGrid;

	// Setup before Case 2
	tempGrid = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
	randomArray = GenerateRandomRowColArray();

	// Case 2: rearrange the rows
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			tempGrid[i][j] = sudokuGrid[randomArray[i]][j];
		}
	}
	sudokuGrid = tempGrid;

	// Setup before Case 3
	tempGrid = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
	randomArray = GenerateRandomArray();

	// Case 3: rearrange the numbers such that all ones become threes, all threes become sixes, etc.
	// Do this randomly. This maintains the solvability of the sudoku while making it look new.
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
	// Every 3 rows can be rearranged among themselves
	// Every block of 3 rows can be rearranged among themselves
	// Same also works for columns
	// This form of scrambling preserves sudoku solvability
	// Example returned randomArray is 8,7,6,1,0,2,4,6,5
	std::vector<int> randomArray;
	std::vector<std::vector<int>> tempArray(3, std::vector<int>(3, 0));
	std::vector<std::vector<int>>::iterator it;
	int i = 0;
	for (int x = 0; x < tempArray.size(); x++)
	{
		for (int y = 0; y < tempArray.size(); y++, i++)
		{
			tempArray[x][y] = i;
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