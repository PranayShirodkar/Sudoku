#include "SudokuGenerator.hpp"

SudokuGenerator::SudokuGenerator()
{
}
SudokuGenerator::~SudokuGenerator()
{
}

int* SudokuGenerator::GetPuzzle()
{
	static int sudokuGrid = 0;
	return &sudokuGrid;
}