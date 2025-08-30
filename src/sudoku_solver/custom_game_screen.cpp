#include "custom_game_screen.h"


custom_game_screen::custom_game_screen()
{
}

//void custom_game_screen::display(sf::RenderWindow& app)
//{
//	app.clear(sf::Color::Black);
//
//	draw_UI();
//
//	for (auto &i : this->list_of_buttons)
//	{
//		app.draw(i.get_outer_button());
//		app.draw(i.get_inner_button());
//	}
//
//	for (auto& i : this->text)
//		app.draw(i);
//
//	app.draw(this->grid);
//
//	if (this->is_indicator_on)
//		app.draw(this->indicator);
//
//	for (auto &i : this->box)
//		app.draw(i);
//
//	draw_numbers();
//	for (auto &i : this->number_sprite)
//		app.draw(i);
//
//	app.display();
//}

screen_name custom_game_screen::run(sf::RenderWindow& app)
{
	init(true);

	app.clear(sf::Color::Black);

	while (app.isOpen())
	{
		// Make sure screen size is playable
		check_screen_size(app);
		
		while (auto event = app.pollEvent())
		{
			screen_name next_screen = event_handler(*event, app);
			if (next_screen != screen_name::CUSTOM)
				return next_screen;
		}

		// Avoid re-printing the puzzle every frame
		// Only re-print when something has happened to the puzzle
		if (this->is_changed)
		{
			display(app);
		}
	}

	return screen_name::END;
}

void custom_game_screen::draw_UI()
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
}

screen_name custom_game_screen::event_handler(sf::Event& event, sf::RenderWindow& app)
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
	return screen_name::CUSTOM;
}

void custom_game_screen::init_buttons()
{
	this->list_of_buttons.clear();
	button solve_button(5.f, sf::Vector2f(260.f, 100.f),
		sf::Vector2f(800.f, 350.f), sf::Color::Green, sf::Color::Black);

	button return_button(5.f, sf::Vector2f(260.f, 100.f),
		sf::Vector2f(800.f, 500.f), sf::Color::Green, sf::Color::Black);

	this->list_of_buttons.push_back(solve_button);
	this->list_of_buttons.push_back(return_button);
}

screen_name custom_game_screen::button_handler(sf::RenderWindow& app)
{
	// Find the selected button
	int button_index = find_button(app);
	if (button_index == -1)
		return screen_name::CUSTOM;

	switch (static_cast<button_name>(button_index))
	{
	case button_name::SOLVE:
		solve_sudoku();
		return screen_name::CUSTOM;
	case button_name::RETURN:
		return screen_name::MENU;
	default:
		return screen_name::CUSTOM;
	}
}

custom_game_screen::~custom_game_screen()
{
}
