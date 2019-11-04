#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace sf;
//constexpr auto gridLength = 9;

class Display
{
private:
	std::string path;
	Texture grid, box, numberTexture;
	Sprite background, highlighter;
	Sprite number[81];

	int xPos[9] = { 25, 89, 151, 216, 280, 342, 404, 466, 528 };
	int yPos[9] = { 124, 186, 249, 314, 377, 440, 503, 565, 628 };
	int LevelOne[9][9] = {
		{ 5,3,0, 0,7,0, 0,0,0 },
		{ 6,0,0, 1,9,5, 0,0,0 },
		{ 0,9,8, 0,0,0, 0,6,0 },
		{ 8,0,0, 0,6,0, 0,0,3 },
		{ 4,0,0, 8,0,3, 0,0,1 },
		{ 7,0,0, 0,2,0, 0,0,6 },
		{ 0,6,0, 0,0,0, 2,8,0 },
		{ 0,0,0, 4,1,9, 0,0,5 },
		{ 0,0,0, 0,8,0, 0,7,9 }
	};
	bool fixed[9][9];

public:
	Display(std::string);
	void SetHighlighterPosition(int, int);
	void SetGrid();
	void DrawWindow(sf::RenderWindow&, bool);
	void GetGameMap(int map[][9]);
	void AssignAnswers(int map[][9]);
	bool IsFixed(int, int);
	~Display();
};

