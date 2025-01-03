#pragma once

#include "gameeventhandler.hpp"
#include <SDL.h>
#include <SDL_ttf.h>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

class Application
{
private:
    static Application* instance_ptr;
    bool running = true;
    Application();
    void SetRunning(bool new_value);

public:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event window_event;
    GameEventHandler event_handler;
    double delta_time = 1;
    static Application* GetInstance()
    {
        if (instance_ptr == nullptr)
        {
            instance_ptr = new Application();
        }
        return instance_ptr;
    }
    ~Application();
    bool GetRunning();
    void Quit() { SetRunning(false); };
    void Update();
    void Render();
};
