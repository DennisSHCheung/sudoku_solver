#include "GameController.h"
using namespace sf;

GameController::GameController()
{
	std::string tempPath = GetPath();
	/* Remove /sudoku_solver.exe from path (Windows only) */
	this->path = tempPath.substr(0, tempPath.find_last_of("\\"));
}

/* Return the location where sudoku_solver.exe is run */
std::string GameController::GetPath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

void GameController::Run()
{
	RenderWindow window(VideoMode(900, 800), "SUDOKU");

	Display screen(this->path);
	GameLogic logic;

	

	/* Initial state */
	std::string state = "sp";
	screen.SetGrid();

	/* True if a box is selected */
	bool pressed = false;

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			else if (e.type == Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == Mouse::Left && state == "sp")
				{
					std::cout << "mouse x: " << e.mouseButton.x << std::endl;
					std::cout << "mouse y: " << e.mouseButton.y << std::endl;
					if (logic.IsWithinScreen(e.mouseButton.x, e.mouseButton.y))
					{
						screen.SetHighlighterPosition(logic.CheckXY(true, e.mouseButton.x), logic.CheckXY(false, e.mouseButton.y));
						pressed = true ? logic.IsFixed(screen) : false;
					}
					else
						pressed = false;
				}
			}
		}
		if (state == "sp")
		{
			screen.DrawWindow(window, pressed);
		}
	}
}

GameController::~GameController()
{
}
