#include <iostream>
#include "Sudoku.hpp"


int main(void)
{
	Sudoku sudokuGame = Sudoku();
	sudokuGame.Print();
	sudokuGame.Solve();
	//int a = sudokuGame.GetNumOfSolns();
	sudokuGame.Print();
	//std::cout << "soln count: " << a << std::endl;

	for (int x = 0; x < NUM_OF_COLUMNS; x++)
	{
		int a,b,c;
		std::cin >> a >> b >> c;
		bool z = sudokuGame.SetNumber(a, b, c);
		sudokuGame.Print();
		std::cout << z << std::endl;
	}

	return 0;
}