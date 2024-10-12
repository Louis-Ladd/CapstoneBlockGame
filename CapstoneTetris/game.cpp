#include "game.h"
Game* Game::instance_ptr = nullptr;

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL was unable to initialize" << std::endl;
		this->renderer = nullptr;
		this->window = nullptr;
		return;
	}

	this->window = SDL_CreateWindow("Tetris",
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									SCREEN_HEIGHT, SCREEN_WIDTH, 0);

	if (!this->window)
	{
		std::cout << "Failed to create SDL window" << std::endl;
		this->renderer = nullptr;
		this->window = nullptr;
		return;
	}

	SDL_SetWindowResizable(this->window, SDL_FALSE);

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);

	if (!this->renderer)
	{
		std::cout << "Failed to create SDL renderer" << std::endl;
		this->renderer = nullptr;
		return;
	}

	return;
}

Game::~Game()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	return;
}

bool Game::GetRunning()
{
	return this->running;
}

void Game::SetRunning(bool new_value)
{
	this->running = new_value;
	return;
}

void Game::Update()
{

}

void Game::Render()
{

}
