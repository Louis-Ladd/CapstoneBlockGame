// mian.cpp : Defines the entry point for the application.
//

#include "main.h"

#include "tetromino/tetrominos.h"	

void handle_events(Game* game)
{
	while (SDL_PollEvent(&game->window_event) > 0)
	{
		switch (game->window_event.type)
		{
			case SDL_QUIT:
				game->SetRunning(false);
				break;
		}
	}
}

int main(int argc, char *argv[])
{
	Game* game = Game::GetInstance();


	if (game->window == nullptr ||
		game->renderer == nullptr)
	{
		return 1;
	}

	Tetris* tetris = Tetris::GetInstance();

	SDL_assert(tetris != nullptr);

	Tetromino I = IShape();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << I.shape[i][j];

		std::cout << std::endl;
	}

	while (game->GetRunning())
	{
		std::cout << SDL_GetTicks() << std::endl;

		// Background Color
		SDL_SetRenderDrawColor(game->renderer, 0, 0, 128, 0);
		SDL_RenderClear(game->renderer);

		// TODO: abstract event handler into a proper inputs class
		handle_events(game);

		tetris->Render(game->renderer);

		SDL_RenderPresent(game->renderer);
	}

	SDL_Quit();
	return 0;
}

