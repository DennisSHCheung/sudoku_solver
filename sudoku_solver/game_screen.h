#pragma once
#include "screen.h"
#include "puzzles.h"
#include "sudoku_logic.h"

class game_screen :
	public screen
{
private:
	enum button_name { SOLVE, RETURN, EXIT };

protected:
	sf::RectangleShape grid;
	std::vector<sf::RectangleShape> box;
	std::vector<sf::Sprite> number_sprite;
	sf::RectangleShape indicator;

	// grid indicator
	bool is_indicator_on;
	bool is_changed;
	int indicator_position;

	// textures used for numbers
	sf::Texture input_number_texture;
	sf::Texture fixed_number_texture;

	// 9x9 grid
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
	screen_name event_handler(sf::Event&event, sf::RenderWindow& app);
	virtual void insert_number(sf::Event& event);
	void check_indicator(sf::RenderWindow& app);
	void solve_sudoku();

	//screen_name button_handler(button_name button);
	void init_buttons();
	screen_name button_handler(sf::RenderWindow& app);
	int find_button(sf::RenderWindow& app);

	~game_screen();
};

