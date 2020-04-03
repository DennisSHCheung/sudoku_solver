#pragma once
#include "screen.h"
#include "puzzles.h"

class game_screen :
	public screen
{
private:
	sf::Texture number_texture;
	int game_puzzle[9][9];
public:
	game_screen();

	virtual screen_name run(sf::RenderWindow& app);

	void load_texture();
	void load_puzzle();

	void draw_grid(std::vector<sf::RectangleShape>& grid, 
					std::vector<sf::RectangleShape>& box, 
					std::vector<sf::Sprite>& number);

	void draw_outer_grid(sf::Vector2f& grid_size, sf::Vector2f& grid_origin, std::vector<sf::RectangleShape>& grid);
	void draw_inner_grid(int x, int y, std::vector<sf::RectangleShape>& box);
	void draw_numbers(int x, int y, int row, int col, std::vector<sf::Sprite>& number);

	~game_screen();
};

