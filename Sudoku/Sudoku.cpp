#include "Sudoku.hpp"

Sudoku::Sudoku()
{
	isValid = true;
	fillCount = 0;
}

Sudoku::~Sudoku()
{
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

void Sudoku::Init(void)
{
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
	srand(time(NULL));
	while (fillCount < 17)
	{
		int r = rand() % 9;
		int c = rand() % 9;
		int val = 1 + (rand() % 9);
		if (NumberCheck(r, c, val) && (sudokuGrid[r][c] == 0))
		{
			AddNumber(r, c, val);
		}
	}
}

bool Sudoku::Solve(int index)
{
	int emptyRow;
	int emptyCol;
	if (!FindEmpty(emptyRow, emptyCol))
	{
		return true;
	}

	for (int i = 0; i < 9; i++)
	{
		if (AddNumber(emptyRow, emptyCol, i + 1))
		{
			if (Solve(0))
			{
				return true;
			}
		}
		DelNumber(emptyRow, emptyCol);
	}

	return false;
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

bool Sudoku::AddNumber(int r, int c, int val)
{
	if (sudokuGrid[r][c] == 0)
	{
		if (NumberCheck(r, c, val))
		{
			sudokuGrid[r][c] = val;
			fillCount++;
			//Print();
			return true;
		}
		else
		{
			sudokuGrid[r][c] = val;
			fillCount++;
			isValid = false;
			//Print();
			return false;
		}
	}
	else
	{
		DelNumber(r, c);
		return AddNumber(r, c, val);
	}
}

void Sudoku::DelNumber(int r, int c)
{
	sudokuGrid[r][c] = 0;
	fillCount--;
	if ((!isValid) && GridCheck())
	{
		isValid = true;
	} // else the gridCheck() failed so the grid remains invalid
	//Print();
}

std::string operator*(const std::string& s, size_t n) {
	std::string result;
	result.reserve(s.size()*n);
	for (size_t i = 0; i < n; ++i) {
		result += s;
	}
	return result;
}