#pragma once
#include "game_screen.h"

class custom_game_screen :
	public game_screen
{
private:
	enum button_name { SOLVE, RETURN };

public:
	custom_game_screen();

	//void display(sf::RenderWindow& app);

	virtual screen_name run(sf::RenderWindow& app);

	screen_name event_handler(sf::Event&event, sf::RenderWindow& app);

	void draw_UI();
	void init_buttons();
	screen_name button_handler(sf::RenderWindow& app);

	~custom_game_screen();
};

