#include "custom_game_screen.h"


custom_game_screen::custom_game_screen()
{
}

screen_name custom_game_screen::run(sf::RenderWindow& app)
{
	// Initialize indicator
	init_indicator();

	// Load number texture
	load_texture();

	// Initialise game grid
	draw_grid();

	init_buttons();

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
	}

	return screen_name::END;
}

screen_name custom_game_screen::event_handler(sf::Event&event, sf::RenderWindow& app)
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
		else
		{
			solve_sudoku();
		}
	}
	else if (event.type = sf::Event::KeyPressed)
	{
		insert_number(event);
	}
	return screen_name::GAME;
}

void custom_game_screen::init_buttons()
{
	button confirm_button(5.f, sf::Vector2f(180.f, 80.f),
		sf::Vector2f(800.f, 350.f), sf::Color::Green, sf::Color::White);

	button return_button(5.f, sf::Vector2f(180.f, 80.f),
		sf::Vector2f(800.f, 500.f), sf::Color::Green, sf::Color::White);

	this->list_of_buttons.push_back(confirm_button);
	this->list_of_buttons.push_back(return_button);
}

screen_name custom_game_screen::button_handler(sf::RenderWindow& app)
{
	screen_name return_screen = screen_name::GAME;

	// Find the selected button
	int button_index = find_button(app);
	if (button_index == -1)
		return return_screen;

	switch (static_cast<button_name>(button_index))
	{
	case button_name::CONFIRM:
		return screen_name::GAME;
	case button_name::RETURN:
		return screen_name::MENU;
	default:
		return screen_name::GAME;
	}
}

custom_game_screen::~custom_game_screen()
{
}
