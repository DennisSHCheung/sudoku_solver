#pragma once
#include "common.h"

class button
{
private:
	sf::RectangleShape outer_button;
	sf::RectangleShape inner_button;

	float line_thickness = 0.f;
	sf::Vector2f outer_size;
	sf::Vector2f button_position;
	sf::Color line_color;
	sf::Color button_color;

public:
	button(float line_thickness, sf::Vector2f outer_size, 
		sf::Vector2f button_position, sf::Color line_color,
		sf::Color button_color);

	button();

	void init_button();

	void set_line_thickness(float line_thickness);
	void set_outer_button_size(sf::Vector2f size);
	void set_button_position(sf::Vector2f position);

	sf::RectangleShape get_outer_button();
	sf::RectangleShape get_inner_button();

	~button();
};

