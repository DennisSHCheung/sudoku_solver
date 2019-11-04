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

GameLogic::~GameLogic()
{
}
