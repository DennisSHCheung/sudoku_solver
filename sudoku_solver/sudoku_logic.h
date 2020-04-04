#pragma once
class sudoku_logic
{
public:
	sudoku_logic();

	static bool is_col_free(int game_puzzle[][9], int col, int num);
	static bool is_row_free(int game_puzzle[][9], int row, int num);
	static bool is_square_free(int game_puzzle[][9], int row, int col, int num);
	static bool is_input_correct(int game_puzzle[][9], int row, int col, int num);

	~sudoku_logic();
};

