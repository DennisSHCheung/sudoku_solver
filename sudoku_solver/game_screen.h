#pragma once
#include "screen.h"

class game_screen :
	public screen
{
public:
	game_screen();

	virtual screen_name run(sf::RenderWindow& app);

	void draw_grid(sf::Vector2u screen_size, std::vector<sf::RectangleShape>& grid);

	~game_screen();
};

