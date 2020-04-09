#pragma once
#include "game_screen.h"

class custom_game_screen :
	public game_screen
{
public:
	custom_game_screen();

	virtual screen_name run(sf::RenderWindow& app);

	bool event_handler(sf::Event&event, sf::RenderWindow& app);

	~custom_game_screen();
};

