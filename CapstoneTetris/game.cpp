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
                                    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, 0);

    if (!this->window)
    {
        LOG("Failed to create SDL window");
        this->renderer = nullptr;
        this->window = nullptr;
        return;
    }

    SDL_SetWindowResizable(this->window, SDL_FALSE);

    LOG("Creating renderer...");
    this->renderer =
        SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);

    if (!this->renderer)
    {
        LOG("Failed to create SDL renderer");
        this->renderer = nullptr;
        return;
    }

    LOG("Initializing Fonts");
    if (TTF_Init() < 0)
    {
        LOG("Unable to initialize fonts");
        return;
    }

    return;
}

Game::~Game()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
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
