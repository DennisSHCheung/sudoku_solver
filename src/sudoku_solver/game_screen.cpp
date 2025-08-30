#include "game_screen.h"
#include "common.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cstring>

game_screen::game_screen()
{
}

void game_screen::display(sf::RenderWindow& app)
{
	app.clear(sf::Color::Black);

	draw_UI();

	for (auto &i : this->list_of_buttons)
	{
		app.draw(i.get_outer_button());
		app.draw(i.get_inner_button());
	}

	for (auto& i : this->text)
		app.draw(i);

	app.draw(this->grid);

	if (this->is_indicator_on)
		app.draw(this->indicator);

	for (auto& i : this->box)
		app.draw(i);

	draw_numbers();
	for (auto& i : this->number_sprite)
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
		
		while (auto event = app.pollEvent())
		{
			screen_name next_screen = event_handler(*event, app);
			if (next_screen != screen_name::GAME)
				return next_screen;
		}		

		// Avoid re-printing the puzzle every frame
		// Only re-print when something has happened to the puzzle
		if (this->is_changed) 
			display(app);
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
				current_origin.x = grid_origin.x + OUTER_GRID_SIZE;
			else
				set_grid_origin(j, current_origin.x);
			
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
			const auto& texture = is_init_exist[i][j] ? YELLOW_NUMBER_TEXTURE : NUMBER_TEXTURE;
			auto sprite = sf::Sprite(texture);

			sf::Vector2f origin = box.at(i * 9 + j).getPosition(); // Get the position of the corresponding box
			ascii_character::set_game_number_texture(sprite, this->game_puzzle[i][j]); // set number texture
			sprite.setScale(sf::Vector2f(5.f, 5.f));
			sprite.setPosition(sf::Vector2f(origin.x + 16.f, origin.y + 16.f));
			this->number_sprite.push_back(sprite);
		}
	}
}

void game_screen::draw_UI()
{
	this->text.clear();
	auto sprite = ascii_character::make_header_sprite("Solve");
	sprite.setPosition(sf::Vector2f(862.f, 380.f));
	sprite.setScale(sf::Vector2f(6.f, 6.f));
	this->text.push_back(sprite);

	sprite = ascii_character::make_header_sprite("Return");
	sprite.setPosition(sf::Vector2f(840.f, 530.f));
	sprite.setScale(sf::Vector2f(6.f, 6.f));
	this->text.push_back(sprite);

	sprite = ascii_character::make_header_sprite("New");
	sprite.setPosition(sf::Vector2f(880.f, 230.f));
	sprite.setScale(sf::Vector2f(6.f, 6.f));
	this->text.push_back(sprite);

}

bool game_screen::key_code_handler(sf::Event& event, int i)
{
	auto* const key = event.getIf<sf::Event::KeyPressed>();
	if (key == nullptr) {
		return false;
	}

	int num = -1;
	using Sc = sf::Keyboard::Scancode;
    switch (key->scancode) {
        case Sc::Num0: case Sc::Numpad0: num = 0; break;
        case Sc::Num1: case Sc::Numpad1: num = 1; break;
        case Sc::Num2: case Sc::Numpad2: num = 2; break;
        case Sc::Num3: case Sc::Numpad3: num = 3; break;
        case Sc::Num4: case Sc::Numpad4: num = 4; break;
        case Sc::Num5: case Sc::Numpad5: num = 5; break;
        case Sc::Num6: case Sc::Numpad6: num = 6; break;
        case Sc::Num7: case Sc::Numpad7: num = 7; break;
        case Sc::Num8: case Sc::Numpad8: num = 8; break;
        case Sc::Num9: case Sc::Numpad9: num = 9; break;
        default: break;
    }
	
	if (num > -1 && (sudoku_logic::is_input_correct(this->game_puzzle, i / 9, i % 9, num) || num == 0))
	{
		this->game_puzzle[i / 9][i % 9] = num;
		return true;
	}
	return false;
}

screen_name game_screen::event_handler(sf::Event& event, sf::RenderWindow& app)
{
	if (event.is<sf::Event::Closed>()) // || event.key.code == sf::Keyboard::Escape
	{
		return screen_name::END;
	}
	else if (auto* const mouse = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouse->button == sf::Mouse::Button::Left)
		{
			check_indicator(app);
			return button_handler(app);
		}
	}
	else if (auto* const key = event.getIf<sf::Event::KeyPressed>())
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
	this->list_of_buttons.clear();
	button solve_button(5.f, sf::Vector2f(260.f, 100.f),
		sf::Vector2f(800.f, 350.f), sf::Color::Green, sf::Color::Black);

	button return_button(5.f, sf::Vector2f(260.f, 100.f),
		sf::Vector2f(800.f, 500.f), sf::Color::Green, sf::Color::Black);

	button new_button(5.f, sf::Vector2f(260.f, 100.f),
		sf::Vector2f(800.f, 200.f), sf::Color::Green, sf::Color::Black);

	this->list_of_buttons.push_back(solve_button);
	this->list_of_buttons.push_back(return_button);
	this->list_of_buttons.push_back(new_button);
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
	case button_name::NEW:
		std::memset(this->game_puzzle, 0, sizeof(this->game_puzzle));
		select_puzzle();
		return screen_name::GAME;
	default:
		return screen_name::GAME;
	}
}

void game_screen::init(bool is_custom)
{
	init_indicator();
	draw_grid();
	init_buttons();
	std::memset(this->game_puzzle, 0, sizeof(this->game_puzzle));
	if (!is_custom)
	{
		load_puzzle();
		select_puzzle();
	}
}

void game_screen::init_indicator()
{
	this->indicator.setSize(sf::Vector2f(BOX_SIZE + 6, BOX_SIZE + 6));
	this->indicator.setFillColor(sf::Color::Green);
	this->is_indicator_on = false;
	this->is_changed = true;
	this->indicator_position = 0;
}

void game_screen::select_puzzle()
{
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> gen_rand_puzzle(0, this->puzzles_count - 1);	
	int random = gen_rand_puzzle(rng);

	while (this->current_puzzle == random)
		random = gen_rand_puzzle(rng);

	this->current_puzzle = random;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			this->game_puzzle[i][j] = this->all_puzzles[random][i][j];
			if (this->game_puzzle[i][j] != 0)
				this->is_init_exist[i][j] = true;
		}			
}

void game_screen::load_puzzle()
{
	auto path = get_current_path();
	path += "/assets/Puzzles.txt";

	this->puzzles_count = 0;
	this->current_puzzle = -1;

	// Create a temporary 3d vector with a size of 100
	std::vector<std::vector<int>> temp_puzzle(9, std::vector<int>(9, 0));
	std::vector<std::vector<std::vector<int>>> temp_vec(100, temp_puzzle);

	std::ifstream file(path);
	if (file.is_open())
	{
		std::string line;
		int row = 0, col = 0, line_count = 0;
		while (std::getline(file, line)) 
		{
			if (line_count == 9)	// New puzzle every 9 lines
			{
				line_count = 0;
				row = 0;
				(this->puzzles_count)++;
				continue;
			}

			int num_count = 0;
			while (num_count < 9)	// Store all 9 numbers on every line
			{
				int num = line[num_count] - '0';	// Convert char to int
				temp_vec[this->puzzles_count][row][num_count] = num;
				num_count++;
			}
			
			row++;
			line_count++;
		}
		file.close();
	}
	
	this->all_puzzles = temp_vec;
}

game_screen::~game_screen()
{
}
