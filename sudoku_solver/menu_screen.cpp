#include "menu_screen.h"

menu_screen::menu_screen()
{
}

screen_name menu_screen::run(sf::RenderWindow& app)
{
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return screen_name::END;
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					return screen_name::GAME;
				else
					return screen_name::CUSTOM;
			}
		}
		app.clear(sf::Color::Black);
		app.display();
	}
	
	return screen_name::END;
}

menu_screen::~menu_screen()
{
}
