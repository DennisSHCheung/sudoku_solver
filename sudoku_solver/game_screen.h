#pragma once
#include "screen.h"
#include "puzzles.h"
#include "sudoku_logic.h"

class game_screen :
	public screen
{
protected:

	sf::RectangleShape grid;
	std::vector<sf::RectangleShape> box;
	std::vector<sf::Sprite> number_sprite;
	sf::RectangleShape indicator;

	bool is_indicator_on = false;
	bool is_changed = true;
	int indicator_position = 0;

	sf::Texture input_number_texture;
	sf::Texture fixed_number_texture;
	int game_puzzle[9][9];
	bool is_init_exist[9][9];

public:
	game_screen();

	virtual screen_name run(sf::RenderWindow& app);

	void init_indicator();
	void load_texture();
	void load_puzzle();

	void set_grid_origin(int index, float& position);
	void draw_grid();

	void draw_inner_grid(sf::Vector2f origin);
	void draw_numbers();

	bool key_code_handler(sf::Event& event, int i);
	virtual bool event_handler(sf::Event&event, sf::RenderWindow& app);
	virtual void insert_number(sf::Event& event);
	void check_indicator(sf::RenderWindow& app);
	void solve_sudoku();

	~game_screen();
};

