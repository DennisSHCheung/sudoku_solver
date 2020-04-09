#include "button.h"

button::button(float line_thickness, sf::Vector2f outer_size, 
	sf::Vector2f button_position, sf::Color line_color,
	sf::Color button_color)
	: 
	line_thickness(line_thickness),
	outer_size(outer_size),
	button_position(button_position),
	line_color(line_color),
	button_color(button_color)
{
	init_button();
}

button::button() : 
	line_thickness(0.f),
	outer_size(sf::Vector2f(0.f, 0.f)),
	button_position(sf::Vector2f(0.f, 0.f)),
	line_color(sf::Color::Yellow),
	button_color(sf::Color::White)
{
}

void button::init_button()
{
	this->outer_button.setPosition(button_position);
	this->outer_button.setSize(outer_size);
	sf::Vector2f inner_size(outer_size.x - line_thickness * 2, outer_size.y - line_thickness * 2);
	sf::Vector2f inner_position(button_position.x + line_thickness, button_position.y + line_thickness);
	this->inner_button.setSize(inner_size);
	this->inner_button.setPosition(inner_position);
	outer_button.setFillColor(line_color);
	inner_button.setFillColor(button_color);
}

sf::RectangleShape button::get_outer_button()
{
	return this->outer_button;
}

sf::RectangleShape button::get_inner_button()
{
	return this->inner_button;
}

button::~button()
{
}
