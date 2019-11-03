#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;

class Display
{
private:
	std::string path;
	Texture grid, box;
	Sprite background, highlighter;

public:
	Display(std::string);
	void SetHighlighterPosition(int, int);
	void DrawWindow(sf::RenderWindow&, bool pressed);
	~Display();
};

