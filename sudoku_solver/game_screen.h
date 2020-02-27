#pragma once
#include "screen.h"

class game_screen :
	public screen
{
public:
	game_screen();

	virtual screen_name run(sf::RenderWindow& app);

	void draw_grid(std::vector<sf::RectangleShape>& grid, std::vector<sf::RectangleShape>& box);

	void draw_outer_grid(sf::Vector2f& grid_size, sf::Vector2f& grid_origin, std::vector<sf::RectangleShape>& grid);
	void draw_inner_grid(int x, int y, std::vector<sf::RectangleShape>& box);

	~game_screen();
};

