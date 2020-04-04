#pragma once
#include "screen.h"
#include "puzzles.h"

class game_screen :
	public screen
{
private:
	sf::Texture input_number_texture;
	sf::Texture fixed_number_texture;
	int game_puzzle[9][9];
	bool is_init_exist[9][9];

	std::vector<int> number_order;
	std::vector<bool> number_is_fixed;
	bool is_init = true;
public:
	game_screen();

	virtual screen_name run(sf::RenderWindow& app);

	void load_texture();
	void load_puzzle();

	void set_grid_origin(int index, float& position);
	void draw_grid(sf::RectangleShape& grid, std::vector<sf::RectangleShape>& box);

	void draw_inner_grid(sf::Vector2f origin, std::vector<sf::RectangleShape>& box);
	void draw_numbers(std::vector<sf::RectangleShape>& box, std::vector<sf::Sprite>& number_sprite);

	bool key_code_handler(sf::Event& event, int i);

	~game_screen();
};

