#pragma once
#include <SFML/Graphics.hpp>

// Minimum screen width for better gaming experience
constexpr auto MIN_SCREEN_WIDTH = 500;
constexpr auto MIN_SCREEN_HEIGHT = 500;

// Thickness of lines
constexpr auto OUTER_GRID_SIZE = 5;
constexpr auto INNER_GRID_SIZE = 2;

constexpr auto BOX_SIZE = 64;

constexpr auto SMALL_GRID = BOX_SIZE + INNER_GRID_SIZE;
constexpr auto LARGE_GRID = SMALL_GRID + OUTER_GRID_SIZE;

// Starting location of the 9x9 grid
constexpr auto GRID_ORIGIN_X = 80;
constexpr auto GRID_ORIGIN_Y = 80;

// States
enum screen_name { MENU, GAME, CUSTOM, END };

// CHARACTER GAP
constexpr auto LARGE_GAP = 30;
constexpr auto SMALL_GAP = 15;

extern sf::Texture HEADER_TEXTURE;
extern sf::Texture NUMBER_TEXTURE;
extern sf::Texture YELLOW_NUMBER_TEXTURE;
