#include "Display.h"
using namespace sf;

Display::Display()
{
	std::string tempPath = GetPath();
	/* Remove /sudoku.exe from path (Windows only) */
	this->path = tempPath.substr(0, tempPath.find_last_of("\\"));
	std::cout << this->path << std::endl;
}

/* Return the location where sudoku.exe is run */
std::string Display::GetPath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

/* Return the correct box based on user input */
int Display::CheckXY(bool isX, int mouseLocation)
{
	int pos = 0;
	if (isX)
	{
		for (int i = 0; i < gridLength; i++)
		{
			if (mouseLocation > xPos[i])
				pos = xPos[i];
			else
				return pos;
		}
	}
	else
	{
		for (int i = 0; i < gridLength; i++)
		{
			if (mouseLocation > yPos[i])
				pos = yPos[i];
			else
				return pos;
		}
	}
	return pos;
}

void Display::Run()
{
	
	RenderWindow window(VideoMode(900, 800), "SUDOKU");
	
	Texture grid, box;
	grid.loadFromFile(this->path + "\\assets\\sudoku_grid.png");
	box.loadFromFile(this->path + "\\assets\\box.png");

	Sprite background(grid);
	background.setPosition(0, 100);
	Sprite rect(box);

	/* True if a box is selected */
	bool pressed = false;

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			else if (e.type == Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == Mouse::Left)
				{
					std::cout << "mouse x: " << e.mouseButton.x << std::endl;
					std::cout << "mouse y: " << e.mouseButton.y << std::endl;
					if ((e.mouseButton.x > 26 && e.mouseButton.x <= 592) && (e.mouseButton.y >= 120 && e.mouseButton.y <= 691))
					{
						rect.setPosition(CheckXY(true, e.mouseButton.x), CheckXY(false, e.mouseButton.y));
						pressed = true;
					}
					else
						pressed = false;
				}
			}
				
		}
		window.clear(Color::White);
		window.draw(background);
		if (pressed)
			window.draw(rect);
		window.display();
	}
	
}

Display::~Display()
{
}
