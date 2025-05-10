#pragma once

#include "../UI/UIManager.hpp"
#include "../application.hpp"
#include <SDL2/SDL.h>

class MainMenu
{
private:
    bool is_open = true;
    Application* game;
    SDL_Renderer* renderer;
    UIManager ui_manager;
    void BuildMainMenu();

public:
    ~MainMenu();
    void HandleMouseClick(SDL_Point point);
    bool GetIsOpen() { return is_open; };
    void Close() { is_open = false; };
    MainMenu(Application* game)
        : game(game), renderer(game->renderer), ui_manager(renderer) {};
    void Start();
};

void RunMainMenu(Application* game);
