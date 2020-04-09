#include "game_screen.h"
#include <iostream>

game_screen::game_screen()
{
}

void game_screen::display(sf::RenderWindow& app)
{
	app.clear(sf::Color::Black);

	for (auto &i : this->list_of_buttons)
	{
		app.draw(i.get_outer_button());
		app.draw(i.get_inner_button());
	}

	app.draw(this->grid);

	if (this->is_indicator_on)
		app.draw(this->indicator);

	for (auto &i : this->box)
		app.draw(i);

	draw_numbers();
	for (auto &i : this->number_sprite)
		app.draw(i);

	app.display();
}

screen_name game_screen::run(sf::RenderWindow &app)
{
	init(false);

	app.clear(sf::Color::Black);
	while (app.isOpen())
	{
		// Make sure screen size is playable
		check_screen_size(app);

		sf::Event event;
		while (app.pollEvent(event))
		{
			screen_name next_screen = event_handler(event, app);
			if ((next_screen == screen_name::END) || (next_screen == screen_name::MENU))
				return next_screen;
		}		

		// Avoid re-printing the puzzle every frame
		// Only re-print when something has happened to the puzzle
		if (this->is_changed)
		{
			display(app);
		}
	}

	// Should never be reached
	return screen_name::END;
}

void game_screen::set_grid_origin(int index, float& position)
{
	if (index == 0 || index == 3 || index == 6)
		position += LARGE_GRID;
	else
		position += SMALL_GRID;
}

void game_screen::draw_grid()
{
	const int full_grid = LARGE_GRID * 4 + SMALL_GRID * 5 - INNER_GRID_SIZE;

	sf::Vector2f grid_size(full_grid, full_grid);
	sf::Vector2f grid_origin(GRID_ORIGIN_X, GRID_ORIGIN_Y);
	this->grid.setSize(grid_size);
	this->grid.setPosition(grid_origin);

	sf::Vector2f current_origin = grid_origin;
	for (int i = 0; i < 9; i++)
	{
		if (i == 0)
			current_origin.y += OUTER_GRID_SIZE;
		for (int j = 0; j < 9; j++)
		{	
			if (j == 0)
			{
				current_origin.x = grid_origin.x + OUTER_GRID_SIZE;
			}
			else
			{
				set_grid_origin(j, current_origin.x);
			}
			
			draw_inner_grid(current_origin);
		}
		set_grid_origin(i + 1, current_origin.y);
	}
}

void game_screen::draw_inner_grid(sf::Vector2f origin)
{
	sf::RectangleShape inner(sf::Vector2f(BOX_SIZE, BOX_SIZE));
	inner.setPosition(origin);
	inner.setFillColor(sf::Color::Black);
	this->box.push_back(inner);
}

void game_screen::draw_numbers()
{
	this->number_sprite.clear();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			// Set numbers to yellow if they are part of the level
			sf::Sprite sprite;
			if (is_init_exist[i][j])
				sprite.setTexture(fixed_number_texture);
			else
				sprite.setTexture(input_number_texture);

			sf::Vector2f origin = box.at(i * 9 + j).getPosition(); // Get the position of the corresponding box
			int x = origin.x;
			int y = origin.y;
			if (this->game_puzzle[i][j] != 0)
				sprite.setTextureRect(sf::IntRect(this->game_puzzle[i][j] * 7 - 7, 0, 7, 8));
			else
				sprite.setTextureRect(sf::IntRect(0, 15, 7, 8));	// Set to empty when number is 0
			sprite.setScale(sf::Vector2f(5.f, 5.f));
			sprite.setPosition(sf::Vector2f(x + 16.f, y + 16.f));
			this->number_sprite.push_back(sprite);
		}
	}
}

bool game_screen::key_code_handler(sf::Event& event, int i)
{
	int num = -1;

	if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0)
		num = 0;
	else if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1)
		num = 1;
	else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2)
		num = 2;
	else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3)
		num = 3;
	else if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4)
		num = 4;
	else if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5)
		num = 5;
	else if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6)
		num = 6;
	else if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7)
		num = 7;
	else if (event.key.code == sf::Keyboard::Num8 || event.key.code == sf::Keyboard::Numpad8)
		num = 8;
	else if (event.key.code == sf::Keyboard::Num9 || event.key.code == sf::Keyboard::Numpad9)
		num = 9;
	
	if (num > -1 && (sudoku_logic::is_input_correct(this->game_puzzle, i / 9, i % 9, num) || num == 0))
	{
		this->game_puzzle[i / 9][i % 9] = num;
		return true;
	}
	return false;
}

screen_name game_screen::event_handler(sf::Event& event, sf::RenderWindow& app)
{
	if (event.type == sf::Event::Closed) // || event.key.code == sf::Keyboard::Escape
	{
		return screen_name::END;
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			check_indicator(app);
			return button_handler(app);
		}
	}
	else if (event.type = sf::Event::KeyPressed)
	{
		insert_number(event);
	}
	return screen_name::GAME;
}

void game_screen::solve_sudoku()
{
	sudoku_logic::solve(game_puzzle);
	this->is_changed = true;
}

void game_screen::check_indicator(sf::RenderWindow& app)
{
	this->is_indicator_on = false;
	this->is_changed = true;
	for (int i = 0; i < this->box.size(); i++)
	{
		if (this->box[i].getGlobalBounds().contains(get_mouse_coord(app)))
		{
			if (!this->is_init_exist[i / 9][i % 9])
			{
				this->indicator.setPosition(sf::Vector2f(this->box[i].getPosition().x - 3.f, box[i].getPosition().y - 3.f));
				this->is_indicator_on = true;
				this->indicator_position = i;
			}
			return;
		}
	}
}

void game_screen::insert_number(sf::Event& event)
{
	if (this->is_indicator_on)
	{
		if (key_code_handler(event, this->indicator_position))
		{
			this->is_changed = true;
			this->is_indicator_on = false;
		}
	}
}

void game_screen::init_buttons()
{
	button solve_button(5.f, sf::Vector2f(180.f, 80.f),
		sf::Vector2f(800.f, 350.f), sf::Color::Green, sf::Color::White);

	button return_button(5.f, sf::Vector2f(180.f, 80.f),
		sf::Vector2f(800.f, 500.f), sf::Color::Green, sf::Color::White);

	this->list_of_buttons.push_back(solve_button);
	this->list_of_buttons.push_back(return_button);
}

int game_screen::find_button(sf::RenderWindow& app)
{
	for (int i = 0; i < this->list_of_buttons.size(); i++)
		if (this->list_of_buttons[i].get_outer_button().getGlobalBounds().contains(get_mouse_coord(app)))
			return i;
	return -1;
}

screen_name game_screen::button_handler(sf::RenderWindow& app)
{
	// Find the selected button
	int button_index = find_button(app);
	if (button_index == -1)
		return screen_name::GAME;

	switch (static_cast<button_name>(button_index))
	{
	case button_name::SOLVE:
		solve_sudoku();
		return screen_name::GAME;
	case button_name::RETURN:
		return screen_name::MENU;
	default:
		return screen_name::GAME;
	}
}

void game_screen::init(bool is_custom)
{
	init_indicator();
	load_texture();
	draw_grid();
	init_buttons();
	if (!is_custom)	load_puzzle();
}

void game_screen::init_indicator()
{
	this->indicator.setSize(sf::Vector2f(BOX_SIZE + 6, BOX_SIZE + 6));
	this->indicator.setFillColor(sf::Color::Green);
	this->is_indicator_on = false;
	this->is_changed = true;
	this->indicator_position = 0;
}

void game_screen::load_texture()
{
	this->input_number_texture.loadFromFile(get_exe_location() + "\\number.png");
	this->fixed_number_texture.loadFromFile(get_exe_location() + "\\number_yellow.png");
}

void game_screen::load_puzzle()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			this->game_puzzle[i][j] = puzzle_2[i][j];
			if (this->game_puzzle[i][j] != 0)
				this->is_init_exist[i][j] = true;
			else
				this->is_init_exist[i][j] = false;
		}
	}
}

game_screen::~game_screen()
{
}
