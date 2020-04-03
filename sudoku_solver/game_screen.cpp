#include "game_screen.h"
#include <iostream>

game_screen::game_screen()
{
}

screen_name game_screen::run(sf::RenderWindow &app)
{
	std::vector<sf::RectangleShape> grid;
	std::vector<sf::RectangleShape> box;
	std::vector<sf::Sprite> number;

	// Load number texture
	load_texture();

	// Load game puzzle
	load_puzzle();

	bool is_changed = true;

	draw_grid(grid, box, number);

	app.clear(sf::Color::Black);
	while (app.isOpen())
	{
		// Make sure screen size is playable
		check_screen_size(app);

		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) // || event.key.code == sf::Keyboard::Escape
			{
				return screen_name::END;
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (auto &i : box)
					{
						if (i.getGlobalBounds().contains(get_mouse_coord(app)))
						{
							// Game Logic
							std::cout << i.getOrigin().x << " " << i.getOrigin().y << "\n";
						}
					}
				}				
			}
			
		}		

		// Avoid re-printing the puzzle every frame
		// Only re-print when something has happened to the puzzle
		if (is_changed)
		{
			app.clear(sf::Color::Black);
			for (int i = 0; i < grid.size(); i++)
			{
				app.draw(grid[i]);
				app.draw(box[i]);
				app.draw(number[i]);
			}
			is_changed = false;
			app.display();
		}
	}

	// Should never be reached
	return screen_name::END;
}

void game_screen::draw_grid(std::vector<sf::RectangleShape>& grid, 
							std::vector<sf::RectangleShape>& box,
							std::vector<sf::Sprite>& number)
{
	// Reset
	grid.clear();
	box.clear();

	sf::Vector2f grid_size(BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE, BOX_SIZE + INNER_GRID_SIZE + OUTER_GRID_SIZE);
	sf::Vector2f grid_origin(GRID_ORIGIN_X, GRID_ORIGIN_Y);

	// Draw top left grid
	draw_outer_grid(grid_size, grid_origin, grid);
	draw_inner_grid(grid_origin.x + OUTER_GRID_SIZE, grid_origin.y + OUTER_GRID_SIZE, box);
	draw_numbers(grid_origin.x + OUTER_GRID_SIZE, grid_origin.y + OUTER_GRID_SIZE, 0, 0, number);

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
		draw_numbers(grid_origin.x, grid_origin.y + OUTER_GRID_SIZE, 0, i + 1, number);
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
		draw_numbers(grid_origin.x + OUTER_GRID_SIZE, grid_origin.y, i + 1, 0, number);
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
			draw_numbers(grid_origin.x, grid_origin.y, i + 1, j + 1, number);
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

void game_screen::draw_numbers(int x, int y, int row, int col, std::vector<sf::Sprite>& number)
{
	sf::Sprite number_sprite(number_texture);
	if (game_puzzle[row][col] != 0)
		number_sprite.setTextureRect(sf::IntRect(game_puzzle[row][col] * 7 - 7, 0, 7, 8));
	else
		number_sprite.setTextureRect(sf::IntRect(0, 15, 7, 8));
	number_sprite.setScale(sf::Vector2f(5.f, 5.f));
	number_sprite.setPosition(sf::Vector2f(x + 16.f, y + 16.f));
	number.push_back(number_sprite);
}

void game_screen::load_texture()
{
	this->number_texture.loadFromFile(get_exe_location() + "\\number.png");
}

void game_screen::load_puzzle()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			this->game_puzzle[i][j] = puzzle_0[i][j];	// change later
		}
	}
}

game_screen::~game_screen()
{
}
