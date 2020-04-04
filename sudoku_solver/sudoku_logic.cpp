#include "sudoku_logic.h"

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

sudoku_logic::~sudoku_logic()
{
}
