#pragma once

#include "common.h"

#include <SFML/Graphics/Sprite.hpp>

class ascii_character
{
public:
	ascii_character();

	static void set_game_number_texture(sf::Sprite& sprite, int num);
	static auto make_header_sprite(std::string header) -> sf::Sprite;

	~ascii_character();
};

