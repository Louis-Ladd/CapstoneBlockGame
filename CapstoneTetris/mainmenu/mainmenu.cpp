#include "mainmenu.hpp"
#include "../UI/UILabeledButton.hpp"
#include "../log.hpp"
#include "SDL_render.h"

void RunMainMenu(Game* game)
{
    MainMenu* main_menu = new MainMenu(game);

    main_menu->Start();

    delete main_menu;
}

MainMenu::~MainMenu() { this->game->event_handler.SetMouseCallback(nullptr); }

// Populates UIManager with UIElements that make up the main menu.
void MainMenu::BuildMainMenu()
{
    this->game->event_handler.SetMouseCallback([this](SDL_Point point)
                                               { HandleMouseClick(point); });
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color dark_cyan = {0, 171, 196, 255};

    UILabel* title = new UILabel(0, 0, this->ui_manager.GetDefaultFont(3),
                                 "Falling Block game", white, this->renderer);
    title->SetPosition({(SCREEN_WIDTH / 2) - (title->GetTextWidth() / 2), 50});

    UILabeledButton* play_button = new UILabeledButton(
        (SCREEN_WIDTH / 2) - 300 / 2, 250, 300, 100, white, dark_cyan,
        this->ui_manager.GetDefaultFont(3), this->renderer, "Play");
    play_button->button->SetOnClickFunction([this](void) { this->Close(); });

    UILabeledButton* quit_button = new UILabeledButton(
        (SCREEN_WIDTH / 2) - 300 / 2, 450, 300, 100, white, red,
        this->ui_manager.GetDefaultFont(3), this->renderer, "Quit");
    quit_button->button->SetOnClickFunction([this](void)
                                            { this->game->Quit(); });

    this->ui_manager.AddUIElement("Title", title);
    this->ui_manager.AddUIElement("Play", play_button);
    this->ui_manager.AddUIElement("Quit", quit_button);
}

// This is our callback for mouse events that give our event handler.
void MainMenu::HandleMouseClick(SDL_Point point)
{
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
