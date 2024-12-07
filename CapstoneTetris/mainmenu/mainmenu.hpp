#pragma once

#include "../UI/UIManager.hpp"
#include "../game.hpp"
#include <SDL.h>

class MainMenu
{
private:
    bool is_open = true;
    Game* game;
    SDL_Renderer* renderer;
    UIManager ui_manager;
    void BuildMainMenu();

public:
    ~MainMenu();
    void HandleMouseClick(SDL_Point point);
    bool GetIsOpen() { return is_open; };
    void Close() { is_open = false; };
    MainMenu(Game* game)
        : game(game), renderer(game->renderer), ui_manager(renderer) {};
    void Start();
};

void RunMainMenu(Game* game);
