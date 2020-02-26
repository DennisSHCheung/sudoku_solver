#pragma once
#include "screen.h"

class menu_screen :
	public screen
{
public:
	menu_screen();

	virtual screen_name run(sf::RenderWindow& app);

	~menu_screen();
};

