#include "sudoku_logic.h"
#include <iostream>

sudoku_logic::sudoku_logic()
{
}

bool sudoku_logic::is_col_free(int game_puzzle[][9], int col, int num)
{
	for (int row = 0; row < 9; row++)
		if (game_puzzle[row][col] == num)
			return false;
	return true;
}

bool sudoku_logic::is_row_free(int game_puzzle[][9], int row, int num)
{
	for (int col = 0; col < 9; col++)
		if (game_puzzle[row][col] == num)
			return false;
	return true;
}

bool sudoku_logic::is_square_free(int game_puzzle[][9], int row, int col, int num)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (game_puzzle[row + i][col + j] == num)
				return false;
	return true;
}

bool sudoku_logic::is_input_correct(int game_puzzle[][9], int row, int col, int num)
{
	return (is_col_free(game_puzzle, col, num) && 
			is_row_free(game_puzzle, row, num) &&
			is_square_free(game_puzzle, row - row % 3, col - col % 3, num));
}

bool sudoku_logic::is_empty(int game_puzzle[][9], int& row, int& col)
{
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (game_puzzle[row][col] == 0)
				return true;
	return false;
}

bool sudoku_logic::solve(int game_puzzle[][9])
{
	int row, col;

	if (!is_empty(game_puzzle, row, col))
		return true;

	for (int num = 1; num <= 9; num++)
	{
		if (is_input_correct(game_puzzle, row, col, num))
		{
			game_puzzle[row][col] = num;
			if (solve(game_puzzle))
				return true;
			game_puzzle[row][col] = 0;
		} 
	}

	return false;
}

sudoku_logic::~sudoku_logic()
{
}
