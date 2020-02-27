#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>

constexpr auto MIN_SCREEN_WIDTH = 500;
constexpr auto MIN_SCREEN_HEIGHT = 500;

constexpr auto OUTER_GRID_SIZE = 5;
constexpr auto INNER_GRID_SIZE = 2;

constexpr auto BOX_SIZE = 64;

constexpr auto GRID_ORIGIN_X = 50;
constexpr auto GRID_ORIGIN_Y = 50;

enum screen_name { MENU, GAME, END };