#include "ascii_character.h"

ascii_character::ascii_character()
{
}

void ascii_character::set_game_number_texture(sf::Sprite& sprite, int num)
{
	if (num == 0)
		sprite.setTextureRect(sf::IntRect({0, 30}, {7, 8}));
	else
		sprite.setTextureRect(sf::IntRect({num * 7 - 7, 0}, {7, 8}));
}

auto ascii_character::make_header_sprite(std::string header) -> sf::Sprite
{
	auto sprite = sf::Sprite(HEADER_TEXTURE);
	if (header == "Time")
		sprite.setTextureRect(sf::IntRect({0, 0}, {17, 7}));
	else if (header == "Custom")
		sprite.setTextureRect(sf::IntRect({0, 8}, {32, 7}));
	else if (header == "Start")
		sprite.setTextureRect(sf::IntRect({0, 16}, {25, 7}));
	else if (header == "Return")
		sprite.setTextureRect(sf::IntRect({0, 24}, {30, 7}));
	else if (header == "Sudoku")
		sprite.setTextureRect(sf::IntRect({0, 32}, {30, 7}));
	else if (header == "Solve")
		sprite.setTextureRect(sf::IntRect({0, 40}, {25, 7}));
	else if (header == "New")
		sprite.setTextureRect(sf::IntRect({0, 48}, {18, 7}));

	return sprite;
}

ascii_character::~ascii_character()
{
}
