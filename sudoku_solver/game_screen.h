#pragma once
#include "screen.h"
#include <fstream>
#include "sudoku_logic.h"
#include "ascii_character.h"
#include <random>

class game_screen :
	public screen
{
private:
	enum button_name { SOLVE, RETURN, NEW };

protected:
	sf::RectangleShape grid;
	std::vector<sf::RectangleShape> box;
	std::vector<sf::Sprite> number_sprite;
	sf::RectangleShape indicator;
	std::vector<sf::Sprite> text;

	// grid indicator
	bool is_indicator_on;
	bool is_changed;
	int indicator_position;

	// 9x9 grid
	int game_puzzle[9][9];
	bool is_init_exist[9][9];
	int puzzles_count;
	int current_puzzle;
	std::vector<std::vector<std::vector<int>>> all_puzzles;

public:
	game_screen();

	virtual screen_name run(sf::RenderWindow& app);
	void display(sf::RenderWindow& app);

	// Initialize game
	void init(bool is_custom);
	void init_indicator();
	void load_puzzle();
	void select_puzzle();
	void set_grid_origin(int index, float& position);
	void draw_grid();
	void draw_inner_grid(sf::Vector2f origin);
	void draw_numbers();
	virtual void draw_UI();

	bool key_code_handler(sf::Event& event, int i);
	screen_name event_handler(sf::Event&event, sf::RenderWindow& app);
	virtual void insert_number(sf::Event& event);
	void check_indicator(sf::RenderWindow& app);
	void solve_sudoku();

	virtual void init_buttons();
	screen_name button_handler(sf::RenderWindow& app);
	int find_button(sf::RenderWindow& app);

	~game_screen();
};

