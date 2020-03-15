// Library Includes
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <stack>

// Project Includes
#include "Sudoku.hpp"
#include "SudokuGenerator.hpp"

// Constants
const int NUM_OF_ROWS = 9;
const int NUM_OF_COLUMNS = 9;

Sudoku::Sudoku()
{
	isValid = true;
	fillCount = 0;
	sudokuGrid = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
	Init();
}

Sudoku::~Sudoku()
{
}

void Sudoku::Init(void)
{
	// get random puzzle from generator
	SudokuGenerator sudokuGenerator = SudokuGenerator();
	sudokuGrid = sudokuGenerator.GetPuzzle();

	// update fill count
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			if (sudokuGrid[i][j] != 0)
			{
				fillCount++;
			}
		}
	}

	//update isValid
	if (!GridCheck())
	{
		isValid = false;
	}

	AddCurrentStateToHistory();

	//srand(int(time(NULL)));
	//while (fillCount < 17)
	//{
	//	int r = rand() % 9;
	//	int c = rand() % 9;
	//	int val = 1 + (rand() % 9);
	//	if (NumberCheck(r, c, val) && (sudokuGrid[r][c] == 0))
	//	{
	//		AddNumber(r, c, val);
	//	}
	//}
}

void Sudoku::Print(void)
{
	system("CLS");
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			if (sudokuGrid[i][j] == 0)
			{
				std::cout << " _ ";
			}
			else
			{
				std::cout << " " << sudokuGrid[i][j] << " ";
			}
			if (((j + 1) % 3 == 0) && ((j + 1) != NUM_OF_COLUMNS))
			{
				std::cout << "|";
			}
		}
		std::cout << std::endl;
		if (((i + 1) % 3 == 0) && ((i + 1) != NUM_OF_ROWS))
		{
			std::cout << (std::string("---") * 9) << "-" << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}
	}
	std::cout << "Grid is " << (isValid ? "valid" : "not valid") << std::endl;
	std::cout << "FillCount is " << fillCount << std::endl;
}

bool Sudoku::Solve()
{
	int emptyRow;
	int emptyCol;
	if (!FindEmpty(emptyRow, emptyCol))
	{
		return true;
	}

	for (int i = 0; i < 9; i++)
	{
		if (SetNumber(emptyRow, emptyCol, i + 1))
		{
			if (Solve())
			{
				return true;
			}
		}
	}
	SetNumber(emptyRow, emptyCol, 0);
	return false;
}

int Sudoku::GetNumOfSolns()
{
	int emptyRow;
	int emptyCol;
	if (!FindEmpty(emptyRow, emptyCol))
	{
		return 1;
	}

	int sum = 0;
	for (int i = 0; i < 9; i++)
	{
		if (SetNumber(emptyRow, emptyCol, i + 1))
		{
			sum += GetNumOfSolns();
		}
	}
	SetNumber(emptyRow, emptyCol, 0);
	return sum;
}

bool Sudoku::FindEmpty(int &r, int &c)
{
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			if (sudokuGrid[i][j] == 0)
			{
				r = i;
				c = j;
				return true;
			}
		}
	}
	return false;
}

bool Sudoku::NumberCheck(int r, int c, int val)
{
	// Case 0: value of 0 is always valid
	if (val == 0)
	{
		return true;
	}

	// Case 1: found duplicate in that row
	for (int x = 0; x < NUM_OF_COLUMNS; x++)
	{
		if (sudokuGrid[r][x] == val)
		{
			if (x != c)
			{
				return false;
			}
		}
	}

	// Case 2: found duplicate in that column
	for (int x = 0; x < NUM_OF_ROWS; x++)
	{
		if (sudokuGrid[x][c] == val)
		{
			if (x != r)
			{
				return false;
			}
		}
	}

	// Case 3: found duplicate in the 3x3 subgrid
	int boxRow = r / 3;
	int boxCol = c / 3;
	for (int x = boxRow * 3; x < ((boxRow * 3) + 3); x++)
	{
		for (int y = boxCol * 3; y < ((boxCol * 3) + 3); y++)
		{
			if (sudokuGrid[x][y] == val)
			{
				if ((x != r) && (y != c))
				{
					return false;
				}
			}
		}
	}

	// Case 4: found no duplicate, check passed
	return true;
}

bool Sudoku::GridCheck(void)
{
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLUMNS; j++)
		{
			if (sudokuGrid[i][j] != 0)
			{
				if (!NumberCheck(i, j, sudokuGrid[i][j]))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Sudoku::SetNumber(int r, int c, int val)
{
	// out of bounds check
	if ((val < 0) || (val > 9))
	{
		return false;
	}
	// already set, just return
	if (sudokuGrid[r][c] == val)
	{
		return false;
	}

	bool retval = false;
	AddCurrentStateToHistory();

	if ((sudokuGrid[r][c] == 0) && (val != 0))
	{
		// new value being set, previously zero, now non-zero
		retval = AddNumber(r, c, val);
	}
	else if ((sudokuGrid[r][c] != 0) && (val == 0))
	{
		// delete the current value, replace with zero
		DelNumber(r, c);
		retval = true;
	}
	else if ((sudokuGrid[r][c] != 0) && (val != 0))
	{
		// replace current value with a new value
		DelNumber(r, c);
		retval = AddNumber(r, c, val);
	}
	//Print();
	return retval;
}

bool Sudoku::AddNumber(int r, int c, int val)
{
	if (NumberCheck(r, c, val))
	{
		sudokuGrid[r][c] = val;
		fillCount++;
		return true;
	}
	else
	{
		sudokuGrid[r][c] = val;
		fillCount++;
		isValid = false;
		return false;
	}
}

void Sudoku::DelNumber(int r, int c)
{
	sudokuGrid[r][c] = 0;
	fillCount--;

	// if the grid was not valid, evaluate if it is valid now
	if ((!isValid) && GridCheck())
	{
		isValid = true;
	}
	// else the gridCheck() failed so the grid remains invalid
}

void Sudoku::AddCurrentStateToHistory()
{
	sudokuGridStateHistory.push(sudokuGrid);
}
bool Sudoku::UndoLastAction()
{
	if (sudokuGridStateHistory.size() < 2)
	{
		return false;
	}
	else
	{
		undoActionHistory.push(sudokuGrid);
		sudokuGrid = sudokuGridStateHistory.top();
		sudokuGridStateHistory.pop();
		Print();
		return true;
	}
}
bool Sudoku::RedoLastUndo()
{
	if (undoActionHistory.size() < 1)
	{
		return false;
	}
	else
	{
		sudokuGridStateHistory.push(sudokuGrid);
		sudokuGrid = undoActionHistory.top();
		undoActionHistory.pop();
		Print();
		return true;
	}
}

std::string operator*(const std::string& s, size_t n) {
	std::string result;
	result.reserve(s.size()*n);
	for (size_t i = 0; i < n; ++i) {
		result += s;
	}
	return result;
}