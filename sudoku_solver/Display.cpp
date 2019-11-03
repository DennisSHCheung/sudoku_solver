#include "Display.h"
using namespace sf;

Display::Display(std::string path) : path(path)
{
	grid.loadFromFile(this->path + "\\assets\\sudoku_grid.png");
	box.loadFromFile(this->path + "\\assets\\box.png");
	background.setTexture(grid);
	background.setPosition(0, 100);
	highlighter.setTexture(box);	
}

void Display::SetHighlighterPosition(int x, int y)
{
	highlighter.setPosition(x, y);
}

void Display::DrawWindow(RenderWindow &window, bool pressed)
{
	window.clear(Color::White);
	window.draw(background);
	if (pressed)
		window.draw(highlighter);
	window.display();
}

Display::~Display()
{
}
