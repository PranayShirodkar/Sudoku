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
	std::vector<std::vector<int>> tempGrid;
	std::vector<int> randomArray;
	for (int x = 0; x < NUM_OF_COLUMNS; x++)
	{
		randomArray.push_back(x);
		tempGrid.push_back(std::vector<int>(9,0));
	}
	random_shuffle(randomArray.begin(), randomArray.end());

	// Case 1: rearrange the columns
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			tempGrid[i][j] = sudokuGrid[i][randomArray[j]];
		}
	}
	sudokuGrid = tempGrid;

	// Clean up after Case 1
	randomArray.clear();
	tempGrid.clear();
	for (int x = 0; x < NUM_OF_COLUMNS; x++)
	{
		randomArray.push_back(x);
		tempGrid.push_back(std::vector<int>(9, 0));
	}
	random_shuffle(randomArray.begin(), randomArray.end());

	// Case 2: rearrange the rows
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			tempGrid[i][j] = sudokuGrid[randomArray[i]][j];
		}
	}
	sudokuGrid = tempGrid;

	// Clean up after Case 2
	randomArray.clear();
	tempGrid.clear();
	for (int x = 0; x < NUM_OF_COLUMNS; x++)
	{
		randomArray.push_back(x);
		tempGrid.push_back(std::vector<int>(9, 0));
	}
	random_shuffle(randomArray.begin(), randomArray.end());

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