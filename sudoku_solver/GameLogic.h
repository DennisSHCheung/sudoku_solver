#pragma once
#include "GameController.h"

constexpr auto gridLength = 9;

class GameLogic
{
private:
	int xPos[gridLength] = { 25, 89, 151, 216, 280, 342, 404, 466, 528 };
	int yPos[gridLength] = { 124, 186, 249, 314, 377, 440, 503, 565, 628 };

public:
	GameLogic();
	int CheckXY(bool, int);
	bool IsWithinScreen(int, int);
	~GameLogic();
};

