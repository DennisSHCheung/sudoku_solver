#pragma once
#include "common.h"
#include "button.h"

class screen
{
public:

	std::vector<button> list_of_buttons;

	virtual screen_name run(sf::RenderWindow& app) = 0;

	//virtual void init_buttons() = 0;

	virtual void check_screen_size(sf::RenderWindow &app)
	{
		if (app.getSize().x <= MIN_SCREEN_WIDTH)
		{
			app.setSize(sf::Vector2u(MIN_SCREEN_WIDTH, app.getSize().y));
		}
		if (app.getSize().y <= MIN_SCREEN_HEIGHT)
		{
			app.setSize(sf::Vector2u(app.getSize().x, MIN_SCREEN_HEIGHT));
		}
	}

	virtual sf::Vector2f get_mouse_coord(sf::RenderWindow& app)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(app); // Mouse position related to the window
		sf::Vector2f translated_position = app.mapPixelToCoords(mouse_position); // Translate mouse position into window coordinates
		return translated_position;
	}

	virtual std::string get_exe_location()
	{
		char result[MAX_PATH];
		std::string path = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
		path = path.substr(0, path.find_last_of("\\"));
		path += "\\assets\\";
		return path;
	}
};