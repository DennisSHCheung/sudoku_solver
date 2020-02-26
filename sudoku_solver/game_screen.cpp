#include "game_screen.h"
#include <iostream>

game_screen::game_screen()
{
}

screen_name game_screen::run(sf::RenderWindow &app)
{

	/*sf::Vertex vertices[] =
	{
		sf::Vertex(sf::Vector2f(0,   0), sf::Color::Red),
		sf::Vertex(sf::Vector2f(0, 100), sf::Color::Red),
		sf::Vertex(sf::Vector2f(100, 100), sf::Color::Red),
		sf::Vertex(sf::Vector2f(100,   0), sf::Color::Red)
	};*/
	// draw it


	std::vector<sf::VertexArray> grid;

	while (app.isOpen())
	{
		check_screen_size(app);

		draw_grid(app.getSize(), grid);

		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
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
		app.display();
	}

	// Should never be reached
	return screen_name::END;
}

void game_screen::draw_grid(sf::Vector2u screen_size, std::vector<sf::VertexArray>& grid)
{
	sf::VertexArray lines(sf::LinesStrip, 4);
	lines[0].position = sf::Vector2f(20, 20);
	lines[0].color = sf::Color::White;
	lines[1].position = sf::Vector2f(20, 300);
	lines[1].color = sf::Color::White;


	lines[2].position = sf::Vector2f(21, 20);
	lines[2].color = sf::Color::White;
	lines[3].position = sf::Vector2f(21, 300);
	lines[3].color = sf::Color::White;
	grid.push_back(lines);
}

game_screen::~game_screen()
{
}
