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
				return screen_name::GAME;
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
