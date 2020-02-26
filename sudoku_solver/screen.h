#pragma once
#include "common.h"

class screen
{
public:
	virtual screen_name run(sf::RenderWindow& app) = 0;

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
};