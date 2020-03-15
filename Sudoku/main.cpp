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

	for (int x = 0; x < 100; x++)
	{
		int abc;
		std::cin >> abc;
		if (abc == 1)
		{
			sudokuGame.UndoLastAction();
		}
		else if (abc == 2)
		{
			sudokuGame.RedoLastUndo();
		}
		else if (abc == 3)
		{
			int a, b, c;
			std::cin >> a >> b >> c;
			bool z = sudokuGame.SetNumber(a, b, c);
			sudokuGame.Print();
			std::cout << z << std::endl;
		}
	}

	return 0;
}