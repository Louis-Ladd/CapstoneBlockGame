#include "game.hpp"
#include "log.hpp"

Game* Game::instance_ptr = nullptr;

Game::Game()
{
    LOG("Init SDL...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG("SDL was unable to initialize");
        this->renderer = nullptr;
        this->window = nullptr;
        return;
    }

    LOG("Creating window...");
    this->window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT,
                                    SCREEN_WIDTH, 0);

    if (!this->window)
    {
        LOG("Failed to create SDL window");
        this->renderer = nullptr;
        this->window = nullptr;
        return;
    }

    SDL_SetWindowResizable(this->window, SDL_FALSE);

    LOG("Creating window");
    this->renderer =
        SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);

    if (!this->renderer)
    {
        LOG("Failed to create SDL renderer");
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

bool Game::GetRunning() { return this->running; }

void Game::SetRunning(bool new_value)
{
    this->running = new_value;
    return;
}

void Game::Update() {}

void Game::Render() {}
