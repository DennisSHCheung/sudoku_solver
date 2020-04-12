#include "ascii_character.h"



ascii_character::ascii_character()
{
}

void ascii_character::set_game_number_texture(sf::Sprite& sprite, int num)
{
	if (num == 0)
		sprite.setTextureRect(sf::IntRect(0, 30, 7, 8));
	else
		sprite.setTextureRect(sf::IntRect(num * 7 - 7, 0, 7, 8));
}

void ascii_character::set_character_texture(sf::Sprite& sprite, char ch)
{
	if (ch == ' ')
		sprite.setTextureRect(sf::IntRect(0, 30, 7, 8));
	else
	{
		if (ch < 'a')
			sprite.setTextureRect(sf::IntRect((ch - 65) * 7, 0, 7, 8));
		else
			sprite.setTextureRect(sf::IntRect((ch - 97) * 7, 7, 7, 8));
	}
}

ascii_character::~ascii_character()
{
}
