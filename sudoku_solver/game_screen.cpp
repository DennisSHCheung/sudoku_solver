#include "game_screen.h"
#include <iostream>

game_screen::game_screen()
{
}

screen_name game_screen::run(sf::RenderWindow &app)
{
	std::vector<sf::RectangleShape> grid;

	while (app.isOpen())
	{
		check_screen_size(app);

		grid.clear();
		draw_grid(app.getSize(), grid);

		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (grid[0].getGlobalBounds().contains(get_mouse_coord(app)))
				{
					std::cout << "Inside\n";
				}
				else
					return screen_name::END;
			}
		}

		

		app.clear(sf::Color::Black);
		//app.draw(vertices, 4, sf::Lines);
		//app.draw(lines);
		for (auto& i : grid)
		{
			app.draw(i);
		}
		//app.draw(left);
		app.display();
	}

	// Should never be reached
	return screen_name::END;
}

void game_screen::draw_grid(sf::Vector2u screen_size, std::vector<sf::RectangleShape>& grid)
{
	sf::RectangleShape left_edge(sf::Vector2f(47.f, 47.f));
	left_edge.setPosition(sf::Vector2f(50.f, 50.f));
	sf::RectangleShape inner(sf::Vector2f(40.f, 40.f));
	inner.setPosition(sf::Vector2f(55.f, 55.f));
	inner.setFillColor(sf::Color::Black);
	grid.push_back(left_edge);
	grid.push_back(inner);
}

game_screen::~game_screen()
{
}
