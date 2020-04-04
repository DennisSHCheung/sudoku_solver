#include "game_screen.h"
#include <iostream>

game_screen::game_screen()
{
}

screen_name game_screen::run(sf::RenderWindow &app)
{
	// Initialises variables
	sf::RectangleShape grid;
	std::vector<sf::RectangleShape> box;
	std::vector<sf::Sprite> number_sprite;

	sf::RectangleShape indicator(sf::Vector2f(BOX_SIZE + 6, BOX_SIZE + 6));
	indicator.setFillColor(sf::Color::Green);

	bool is_indicator_on = false;
	bool is_changed = true;
	int indicator_position = 0;

	// Load number texture
	load_texture();

	// Load game puzzle
	load_puzzle();

	draw_grid(grid, box);

	app.clear(sf::Color::Black);
	while (app.isOpen())
	{
		// Make sure screen size is playable
		check_screen_size(app);

		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) // || event.key.code == sf::Keyboard::Escape
			{
				return screen_name::END;
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					is_indicator_on = false;
					is_changed = true;
					for (int i = 0; i < box.size(); i++)
					{
						if (box[i].getGlobalBounds().contains(get_mouse_coord(app)))
						{
							if (!is_init_exist[i / 9][i % 9])
							{
								indicator.setPosition(sf::Vector2f(box[i].getPosition().x - 3.f, box[i].getPosition().y - 3.f));
								is_indicator_on = true;
								indicator_position = i;
							}
							break;
						}
					}
				}				
			}
			else if (event.type = sf::Event::KeyPressed)
			{
				if (is_indicator_on)
				{
					if (key_code_handler(event, indicator_position))
					{
						is_changed = true;
						is_indicator_on = false;
					}
				}
				
			}
			
		}		

		// Avoid re-printing the puzzle every frame
		// Only re-print when something has happened to the puzzle
		if (is_changed)
		{
			app.clear(sf::Color::Black);

			app.draw(grid);

			if (is_indicator_on)
				app.draw(indicator);

			for (auto &i : box)
				app.draw(i);

			draw_numbers(box, number_sprite);
			for (auto &i : number_sprite)
				app.draw(i);

			app.display();
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

void game_screen::draw_grid(sf::RectangleShape& grid, std::vector<sf::RectangleShape>& box)
{
	const int full_grid = LARGE_GRID * 4 + SMALL_GRID * 5 - INNER_GRID_SIZE;

	sf::Vector2f grid_size(full_grid, full_grid);
	sf::Vector2f grid_origin(GRID_ORIGIN_X, GRID_ORIGIN_Y);

	sf::RectangleShape outer_grid(grid_size);
	outer_grid.setPosition(grid_origin);
	grid = outer_grid;

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
			
			draw_inner_grid(current_origin, box);
		}
		set_grid_origin(i + 1, current_origin.y);
	}
}

void game_screen::draw_inner_grid(sf::Vector2f origin, std::vector<sf::RectangleShape>& box)
{
	sf::RectangleShape inner(sf::Vector2f(BOX_SIZE, BOX_SIZE));
	inner.setPosition(origin);
	inner.setFillColor(sf::Color::Black);
	box.push_back(inner);
}

void game_screen::draw_numbers(std::vector<sf::RectangleShape>& box, std::vector<sf::Sprite>& number_sprite)
{
	number_sprite.clear();
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
				sprite.setTextureRect(sf::IntRect(game_puzzle[i][j] * 7 - 7, 0, 7, 8));
			else
				sprite.setTextureRect(sf::IntRect(0, 15, 7, 8));	// Set to empty when number is 0
			sprite.setScale(sf::Vector2f(5.f, 5.f));
			sprite.setPosition(sf::Vector2f(x + 16.f, y + 16.f));
			number_sprite.push_back(sprite);
		}
	}
}

bool game_screen::key_code_handler(sf::Event& event, int i)
{
	int num = -1;
	switch (event.key.code)
	{
		case sf::Keyboard::Num0:
			num = 0;
			break;
		case sf::Keyboard::Num1:
			num = 1;
			break;
		case sf::Keyboard::Num2:
			num = 2;
			break;
		case sf::Keyboard::Num3:
			num = 3;
			break;
		case sf::Keyboard::Num4:
			num = 4;
			break;
		case sf::Keyboard::Num5:
			num = 5;
			break;
		case sf::Keyboard::Num6:
			num = 6;
			break;
		case sf::Keyboard::Num7:
			num = 7;
			break;
		case sf::Keyboard::Num8:
			num = 8;
			break;
		case sf::Keyboard::Num9:
			num = 9;
			break;
	}
	if (num > -1 && sudoku_logic::is_input_correct(this->game_puzzle, i / 9, i % 9, num) || num == 0)
	{
		this->game_puzzle[i / 9][i % 9] = num;
		return true;
	}
	return false;
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
			this->game_puzzle[i][j] = puzzle_0[i][j];
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
