#include <iostream>
#include "Sudoku.hpp"


int main(void)
{
	Sudoku sudokuGame = Sudoku();
	sudokuGame.Print();
	sudokuGame.Solve();
	sudokuGame.Print();

	for (int x = 0; x < NUM_OF_COLUMNS; x++)
	{
		int a,b,c;
		std::cin >> a >> b >> c;
		bool z = sudokuGame.AddNumber(a, b, c);
		sudokuGame.Print();
		std::cout << z << std::endl;
	}

	return 0;
}