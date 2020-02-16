#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int NUM_OF_ROWS = 9;
const int NUM_OF_COLUMNS = 9;

class Sudoku
{
public:
	Sudoku();
	~Sudoku();
	void Print(void);
	void Init(void);
	bool Solve(int index);
	bool FindEmpty(int &r, int &c);
	bool NumberCheck(int r, int c, int val);
	bool GridCheck(void);
	bool AddNumber(int r, int c, int val);
	void DelNumber(int r, int c);
	
private:
	//int sudokuGrid[NUM_OF_ROWS][NUM_OF_COLUMNS] = { 0 };

	int sudokuGrid[NUM_OF_ROWS][NUM_OF_COLUMNS] = {
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
	bool isValid;
	int fillCount;

};

std::string operator*(const std::string& s, size_t n);
