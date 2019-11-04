#pragma once
#include "GameController.h"

class GameLogic
{
private:
	int xPos[9] = { 25, 89, 151, 216, 280, 342, 404, 466, 528 };
	int yPos[9] = { 124, 186, 249, 314, 377, 440, 503, 565, 628 };
	int selectedX, selectedY;

public:
	GameLogic();
	int CheckXY(bool, int);
	bool IsFixed(Display&);
	bool IsWithinScreen(int, int);
	~GameLogic();
};

