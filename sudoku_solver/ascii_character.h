#pragma once
#include "common.h"

class ascii_character
{
public:
	ascii_character();

	static void set_game_number_texture(sf::Sprite& sprite, int num);
	static void set_header_texture(sf::Sprite& sprite, std::string header);

	~ascii_character();
};

