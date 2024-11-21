#pragma once

#include "input.hpp"
#include <SDL.h>
#include <SDL_ttf.h>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

class Game
{
private:
    static Game* instance_ptr;
    bool running = true;
    Game();
    void SetRunning(bool new_value);

public:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event window_event;
    GameEventHandler event_handler;
    double delta_time = 1;
    static Game* GetInstance()
    {
        if (instance_ptr == nullptr)
        {
            instance_ptr = new Game();
        }
        return instance_ptr;
    }
    ~Game();
    bool GetRunning();
    void Quit() { SetRunning(false); };
    void Update();
    void Render();
};
