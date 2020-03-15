#pragma once

// Library Includes
#include <vector>
#include <stack>

extern const int NUM_OF_ROWS;
extern const int NUM_OF_COLUMNS;

class Sudoku
{
public:
	Sudoku();
	~Sudoku();
	void Print(void);
	void Init(void);
	bool Solve();
	int GetNumOfSolns();
	bool FindEmpty(int &r, int &c);
	bool NumberCheck(int r, int c, int val);
	bool GridCheck(void);
	bool SetNumber(int r, int c, int val);
	void AddCurrentStateToHistory();
	bool UndoLastAction();
	bool RedoLastUndo();
	
private:
	// private methods
	bool AddNumber(int r, int c, int val);
	void DelNumber(int r, int c);

	//private members
	std::vector<std::vector<int>> sudokuGrid;
	std::stack<std::vector<std::vector<int>>> sudokuGridStateHistory;
	std::stack<std::vector<std::vector<int>>> undoActionHistory;
	bool isValid;
	int fillCount;

};

std::string operator*(const std::string& s, size_t n);
