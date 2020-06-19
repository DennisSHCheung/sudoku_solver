#include "menu_screen.h"

menu_screen::menu_screen()
{
}

void menu_screen::display(sf::RenderWindow& app)
{
	app.clear(sf::Color::Black);

	for (auto &i : this->list_of_buttons)
	{
		app.draw(i.get_outer_button());
		app.draw(i.get_inner_button());
	}

	for (auto& i : this->text)
		app.draw(i);

	app.display();
}

screen_name menu_screen::run(sf::RenderWindow& app)
{
	init();

	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			screen_name next_screen = event_handler(event, app);
			if ((next_screen == screen_name::END) || (next_screen == screen_name::GAME))
				return next_screen;
		}
		
		if (this->is_changed)
			display(app);
	}
	
	return screen_name::END;
}

void menu_screen::draw_UI()
{
	this->text.clear();
	sf::Sprite sprite;
	sprite.setPosition(sf::Vector2f(505.f, 480.f));
	ascii_character::set_header_texture(sprite, "Custom");
	sprite.setScale(sf::Vector2f(6.f, 6.f));
	this->text.push_back(sprite);

	sprite.setPosition(sf::Vector2f(525.f, 630.f));
	ascii_character::set_header_texture(sprite, "Start");
	sprite.setScale(sf::Vector2f(6.f, 6.f));
	this->text.push_back(sprite);

	sprite.setPosition(sf::Vector2f(455.f, 230.f));
	ascii_character::set_header_texture(sprite, "Sudoku");
	sprite.setScale(sf::Vector2f(10.f, 10.f));
	this->text.push_back(sprite);

}

void menu_screen::init()
{
	draw_UI();
	init_buttons();
	this->is_changed = true;
}

screen_name menu_screen::event_handler(sf::Event& event, sf::RenderWindow& app)
{
	if (event.type == sf::Event::Closed) // || event.key.code == sf::Keyboard::Escape
	{
		return screen_name::END;
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			return button_handler(app);
		}
	}
	return screen_name::MENU;
}

int menu_screen::find_button(sf::RenderWindow& app)
{
	for (int i = 0; i < this->list_of_buttons.size(); i++)
		if (this->list_of_buttons[i].get_outer_button().getGlobalBounds().contains(get_mouse_coord(app)))
			return i;
	return -1;
}

screen_name menu_screen::button_handler(sf::RenderWindow& app)
{
	// Find the selected button
	int button_index = find_button(app);
	if (button_index == -1)
		return screen_name::MENU;

	switch (static_cast<button_name>(button_index))
	{
	case button_name::START:
		return screen_name::GAME;	// todo: custom
	case button_name::CUSTOM:
		return screen_name::GAME;
	default:
		return screen_name::GAME;
	}

}

void menu_screen::init_buttons()
{
	this->list_of_buttons.clear();
	button custom_button(5.f, sf::Vector2f(260.f, 100.f),
		sf::Vector2f(470.f, 450.f), sf::Color::Green, sf::Color::Black);

	button start_button(5.f, sf::Vector2f(260.f, 100.f),
		sf::Vector2f(470.f, 600.f), sf::Color::Green, sf::Color::Black);

	this->list_of_buttons.push_back(custom_button);
	this->list_of_buttons.push_back(start_button);
}

menu_screen::~menu_screen()
{
}
