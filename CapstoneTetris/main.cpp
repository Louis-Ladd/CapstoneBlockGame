// mian.cpp : Defines the entry point for the application.
//

#include "main.h"

void handle_events(Game& game)
{
	while (SDL_PollEvent(&game.window_event) > 0)
	{
		switch (game.window_event.type)
		{
			case SDL_QUIT:
				game.stop_running();
				break;
		}
	}
}

int main(int argc, char *argv[])
{
	Game game("Tetris");

	if (game.window == nullptr ||
		game.renderer == nullptr)
	{
		return 1;
	}

	while (game.is_running())
	{
		std::cout << SDL_GetTicks() << std::endl;
		handle_events(game);
	}

	SDL_Quit();
	return 0;
}

