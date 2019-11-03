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
	for (int i = 0; i < gridLength; i++)
	{
		if (mouseLocation > *ptr)
		{
			pos = *ptr;
			ptr++;
		}
		else
			return pos;
	}
	return pos;
}

GameLogic::~GameLogic()
{
}
