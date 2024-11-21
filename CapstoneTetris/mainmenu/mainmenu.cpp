#include "mainmenu.hpp"
#include "../UI/UIButton.hpp"
#include "../log.hpp"
#include "SDL_render.h"

void RunMainMenu(SDL_Renderer* renderer, Game* game)
{
    MainMenu* main_menu = new MainMenu(game->renderer, game);

    main_menu->Start();

    delete main_menu;
}

MainMenu::~MainMenu() { this->game->event_handler.SetMouseCallback(nullptr); }

void MainMenu::BuildMainMenu()
{
    this->game->event_handler.SetMouseCallback([this](SDL_Point point)
                                               { HandleMouseClick(point); });
    SDL_Color dark_cyan = {0, 171, 196, 255};
    UIButton* button =
        new UIButton((SCREEN_WIDTH / 2) - 300 / 2, 300, 300, 100, dark_cyan);
    button->SetOnClickFunction([this](void) { this->Close(); });
    this->ui_manager.AddUIElement("Play", button);

    SDL_Color red = {255, 0, 0, 255};
    button = new UIButton((SCREEN_WIDTH / 2) - 300 / 2, 450, 300, 100, red);
    button->SetOnClickFunction([this](void) { this->game->Quit(); });
    this->ui_manager.AddUIElement("Quit", button);
}

void MainMenu::HandleMouseClick(SDL_Point point)
{
    LOG("Click at: x:%i y:%i", point.x, point.y);
    this->ui_manager.InvokeClickEvents(point);
}

void MainMenu::Start()
{
    BuildMainMenu();
    while (game->GetRunning() && this->GetIsOpen())
    {
        SDL_SetRenderDrawColor(this->game->renderer, 0, 0, 0, 0);
        SDL_RenderClear(this->game->renderer);

        this->game->event_handler.HandleEvent(this->game);
        this->ui_manager.Render();

        SDL_RenderPresent(this->game->renderer);
    }
}
