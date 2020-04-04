//#pragma once
//#include "GameController.h"
//
//class GameLogic
//{
//private:
//	int xPos[9] = { 25, 89, 151, 216, 280, 342, 404, 466, 528 };
//	int yPos[9] = { 124, 186, 249, 314, 377, 440, 503, 565, 628 };
//	int selectedX, selectedY;
//	int answerMap[9][9];
//
//public:
//	GameLogic();
//	int CheckXY(bool, int);
//	bool IsFixed(Display&);
//	bool IsWithinScreen(int, int);
//
//	bool SudokuSolver(int grid[9][9]);
//	/* Help functions for SudokuSolver */
//	bool FindEmptyLocation(int[9][9], int&, int&);
//	bool CheckCol(int[9][9], int col, int num);
//	bool CheckRow(int[9][9], int, int);
//	bool CheckSquare(int[9][9], int, int, int);
//	bool IsFree(int[9][9], int, int, int);
//
//
//	~GameLogic();
//};
//
