#include "GameLogic.h"

GameLogic::GameLogic()
{
}

bool GameLogic::IsWithinScreen(int x, int y)
{
	if ((x > 26 && x <= 592) && (y >= 125 && y <= 691))
		return true;
	return false;
}

/* Return the correct box based on user input */
int GameLogic::CheckXY(bool isX, int mouseLocation)
{
	int pos = 0;
	int *ptr = isX ? xPos : yPos;
	for (int i = 0; i < 9; i++)
	{
		
		if (mouseLocation > *ptr)
		{
			pos = *ptr;
			ptr++;
		}
		else
		{
			if (isX)
				selectedX = --i;
			else
				selectedY = --i;
			std::cout << selectedX << "  " << selectedY << "   " << --i << std::endl;
			return pos;
		}
			
	}
	if (isX)
		selectedX = 8;
	else
		selectedY = 8;
	std::cout << selectedX << "  " << selectedY << std::endl;
	return pos;
}

bool GameLogic::IsFixed(Display &screen)
{
	if (screen.IsFixed(selectedX, selectedY))
		return true;
	return false;
}

bool GameLogic::SudokuSolver(int grid[9][9])
{
	int row, col;

	if (!FindEmptyLocation(grid, row, col))
		return true;

	for (int num = 1; num <= 9; num++)
	{
		if (IsFree(grid, row, col, num))
		{
			grid[row][col] = num;
			if (SudokuSolver(grid))
				return true;
			grid[row][col] = 0;
		}
	}
	
	return false;
}

bool GameLogic::FindEmptyLocation(int grid[9][9], int &row, int &col)
{
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (grid[row][col] == 0)
				return true;
	return false;
}

bool GameLogic::CheckCol(int grid[9][9], int col, int num)
{
	for (int row = 0; row < 9; row++)
		if (grid[row][col] == num)
			return true;
	return false;
}

bool GameLogic::CheckRow(int grid[9][9], int row, int num)
{
	for (int col = 0; col < 9; col++)
		if (grid[row][col] == num)
			return true;
	return false;
}

bool GameLogic::CheckSquare(int grid[9][9], int r, int c, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + r]
				[col + c] == num)
				return true;
	return false;
}

bool GameLogic::IsFree(int grid[9][9], int row, int col, int num)
{
	return !CheckRow(grid, row, num) &&	!CheckCol(grid, col, num) &&
		!CheckSquare(grid, row - row % 3, col - col % 3, num) && grid[row][col] == 0;
}



GameLogic::~GameLogic()
{
}
