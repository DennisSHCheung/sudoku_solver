#pragma once
#include "screen.h"
#include "ascii_character.h"

class menu_screen :
	public screen
{
private:
	std::vector<sf::Sprite> text;
	bool is_changed;
	enum button_name { CUSTOM, START };

public:
	menu_screen();

	void display(sf::RenderWindow& app);
	void draw_UI();
	void init();
	void init_buttons();

	screen_name event_handler(sf::Event& event, sf::RenderWindow& app);
	int find_button(sf::RenderWindow& app);
	screen_name button_handler(sf::RenderWindow& app);


	virtual screen_name run(sf::RenderWindow& app);

	~menu_screen();
};

