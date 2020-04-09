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

	app.clear(sf::Color::Black);
	while (app.isOpen())
	{

		// Make sure screen size is playable
		check_screen_size(app);

		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event_handler(event, app))
				return screen_name::END;
		}

		// Avoid re-printing the puzzle every frame
		// Only re-print when something has happened to the puzzle
		if (this->is_changed)
		{
			app.clear(sf::Color::Black);

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

bool custom_game_screen::event_handler(sf::Event&event, sf::RenderWindow& app)
{
	if (event.type == sf::Event::Closed) // || event.key.code == sf::Keyboard::Escape
	{
		return true;
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			check_indicator(app);
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
	return false;
}

custom_game_screen::~custom_game_screen()
{
}
