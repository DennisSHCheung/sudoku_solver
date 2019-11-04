#include "Display.h"
using namespace sf;

Display::Display(std::string path) : path(path)
{
	grid.loadFromFile(this->path + "\\assets\\sudoku_grid.png");
	box.loadFromFile(this->path + "\\assets\\box.png");
	background.setTexture(grid);
	background.setPosition(0, 100);
	highlighter.setTexture(box);	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			fixed[i][j] = (LevelOne[i][j] == 0) ? true : false;
	}
}

void Display::SetGrid()
{
	numberTexture.loadFromFile(this->path + "\\assets\\number.png");
	int initPos = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Sprite tempSprite(numberTexture);
			if (LevelOne[j][i] != 0)			
				tempSprite.setTextureRect(IntRect(LevelOne[j][i]*7-7, 0, 7, 8));
			else
				tempSprite.setTextureRect(IntRect(0, 15, 7, 8));
			
			tempSprite.setScale(Vector2f(5, 5));
			//tempSprite.setPosition(41, 137);
			tempSprite.setPosition(xPos[i] + 16, yPos[j] + 13);
			number[j*9 + i] = tempSprite;
		}
	}
}

void Display::SetHighlighterPosition(int x, int y)
{
	highlighter.setPosition(x, y);
}

bool Display::IsFixed(int x, int y)
{
	return fixed[y][x];
}

void Display::DrawWindow(RenderWindow &window, bool pressed)
{
	window.clear(Color::White);
	window.draw(background);
	if (pressed)
		window.draw(highlighter);
	for (int i = 0; i < 81; i++)
		window.draw(number[i]);
	window.display();
}

Display::~Display()
{
}
