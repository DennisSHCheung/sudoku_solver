#include "game_screen.h"
#include <iostream>

game_screen::game_screen()
{
}

screen_name game_screen::run(sf::RenderWindow &app)
{
	std::vector<sf::RectangleShape> grid;
	std::vector<sf::RectangleShape> box;

	while (app.isOpen())
	{
		check_screen_size(app);

		grid.clear();
		box.clear();
		draw_grid(grid, box);

		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
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
		for (int i = 0; i < grid.size(); i++)
		{
			app.draw(grid[i]);
			app.draw(box[i]);
		}
		app.display();
	}

	// Should never be reached
	return screen_name::END;
}

void game_screen::draw_grid(std::vector<sf::RectangleShape>& grid, std::vector<sf::RectangleShape>& box)
{
	sf::Vector2f grid_size(BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE, BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE);
	sf::Vector2f grid_origin(GRID_ORIGIN_X, GRID_ORIGIN_Y);

	// Draw top left grid
	draw_outer_grid(grid_size, grid_origin, grid);
	draw_inner_grid(grid_origin.x + OUTER_GRID_SIZE, grid_origin.y + OUTER_GRID_SIZE, box);

	// Draw grids on 1st column
	for (int i = 0; i < 8; i++)
	{
		grid_origin.x += grid_size.x;
		if (i == 1 || i == 4 || i == 7)
		{
			grid_size.x = BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE;
		}
		else
		{
			grid_size.x = BOX_SIZE + INNER_GRID_SIZE;
		}

		draw_outer_grid(grid_size, grid_origin, grid);

		draw_inner_grid(grid_origin.x, grid_origin.y + OUTER_GRID_SIZE, box);
	}

	// Draw grids on 1st row
	grid_origin.x = GRID_ORIGIN_X;
	for (int i = 0; i < 8; i++)
	{
		grid_origin.y += grid_size.y;
		if (i == 1 || i == 4 || i == 7)
		{
			grid_size.y = BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE;
		}
		else
		{
			grid_size.y = BOX_SIZE + INNER_GRID_SIZE;
		}

		draw_outer_grid(grid_size, grid_origin, grid);

		draw_inner_grid(grid_origin.x + OUTER_GRID_SIZE, grid_origin.y, box);
	}

	// Reset
	grid_size = { BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE , BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE };
	grid_origin.x = GRID_ORIGIN_X;
	grid_origin.y = GRID_ORIGIN_Y;

	// Draw the rest of the grids
	for (int i = 0; i < 8; i++)
	{
		grid_origin.y += grid_size.y;
		if (i == 1 || i == 4 || i == 7)
		{
			grid_size.y = BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE;
		}
		else
		{
			grid_size.y = BOX_SIZE + INNER_GRID_SIZE;
		}
		
		for (int j = 0; j < 8; j++)
		{
			grid_origin.x += grid_size.x;
			if (j == 1 || j == 4 || j == 7)
			{
				grid_size.x = BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE;
			}
			else
			{
				grid_size.x = BOX_SIZE + INNER_GRID_SIZE;
			}

			draw_outer_grid(grid_size, grid_origin, grid);
			draw_inner_grid(grid_origin.x, grid_origin.y, box);
		}
		grid_origin.x = GRID_ORIGIN_X;
	}
	
	
}

void game_screen::draw_outer_grid(sf::Vector2f& grid_size, sf::Vector2f& grid_origin, std::vector<sf::RectangleShape>& grid)
{
	sf::RectangleShape outer(sf::Vector2f(grid_size.x, grid_size.y));
	outer.setPosition(sf::Vector2f(grid_origin.x, grid_origin.y));
	grid.push_back(outer);
}

void game_screen::draw_inner_grid(int x, int y, std::vector<sf::RectangleShape>& box)
{
	sf::RectangleShape inner(sf::Vector2f(BOX_SIZE, BOX_SIZE));
	inner.setPosition(sf::Vector2f(x, y));
	inner.setFillColor(sf::Color::Black);
	box.push_back(inner);
}

game_screen::~game_screen()
{
}
