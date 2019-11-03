#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <windows.h>

constexpr auto gridLength = 9;

class Display
{
private:
	std::string path;
	int xPos[gridLength] = { 25, 89, 151, 216, 280, 342, 404, 466, 528 };
	int yPos[gridLength] = { 124, 186, 251, 314, 377, 440, 503, 565, 628 };

public:
	Display();
	std::string GetPath();
	int CheckXY(bool, int);
	void Run();
	~Display();
};

