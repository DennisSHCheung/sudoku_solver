#pragma once
#include "common.h"

class ascii_character
{
public:
	ascii_character();

	static void set_game_number_texture(sf::Sprite& sprite, int num);
	static void set_character_texture(sf::Sprite& sprite, char ch);

	~ascii_character();
};

