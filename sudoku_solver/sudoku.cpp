//#include "GameController.h"
#include "common.h"
#include "menu_screen.h"
#include "game_screen.h"
#include "custom_game_screen.h"

int main(int argc, char* argv[])
{
	/*GameController controller;
	controller.Run();*/

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