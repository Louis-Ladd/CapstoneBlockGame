#pragma once

#include "input.hpp"
#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 600

class Game {
  private:
    static Game* instance_ptr;
    bool running = true;
    Game();

  public:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event window_event;
    GameEventHandler event_handler;
    static Game* GetInstance() {
        if (instance_ptr == nullptr) {
            instance_ptr = new Game();
        }
        return instance_ptr;
    }
    ~Game();
    bool GetRunning();
    void SetRunning(bool new_value);
    void Update();
    void Render();
};
