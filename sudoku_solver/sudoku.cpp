//#include "GameController.h"
#include "common.h"
#include "menu_screen.h"
#include "game_screen.h"
#include "custom_game_screen.h"

sf::Texture NUMBER_TEXTURE;
sf::Texture YELLOW_NUMBER_TEXTURE;
sf::Texture HEADER_TEXTURE;

std::string get_exe_location()
{
	char result[MAX_PATH];
	std::string path = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
	path = path.substr(0, path.find_last_of("\\"));
	path += "\\assets\\";
	return path;
}

void init_texture()
{
	std::string path = get_exe_location();
	NUMBER_TEXTURE.loadFromFile(path + "\\number.png");
	YELLOW_NUMBER_TEXTURE.loadFromFile(path + "\\number_yellow.png");
	HEADER_TEXTURE.loadFromFile(path + "\\headers.png");
}

int main(int argc, char* argv[])
{
	init_texture();

	std::vector<screen*> screens;
	screen_name current_screen = screen_name::MENU;

	sf::RenderWindow app(sf::VideoMode(1200, 800), "SUDOKU");

	menu_screen menu;
	game_screen sudoku;
	custom_game_screen custom;
	
	/** Store all available screens */
	screens.push_back(&menu);
	screens.push_back(&sudoku);
	screens.push_back(&custom);

	while (current_screen != screen_name::END)
	{
		current_screen = screens[current_screen]->run(app);
	}
	app.close();

	return EXIT_SUCCESS;
}