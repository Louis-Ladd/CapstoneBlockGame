// main.cpp : Defines the entry point for the application.
//

#include "main.hpp"

int main(int argc, char* argv[]) {
    std::cout << "Game starting..." << std::endl;

    Game* game = Game::GetInstance();

    if (game->window == nullptr || game->renderer == nullptr) {
        return 1;
    }

    Tetris* tetris = Tetris::GetInstance();

    SDL_assert(tetris != nullptr);

    std::cout << "Press space to go through queue" << std::endl;

    while (game->GetRunning()) {

        // Background Color
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 128, 0);
        SDL_RenderClear(game->renderer);

        game->event_handler.HandleEvent(game);

        tetris->Update();
        tetris->Render(game->renderer);

        SDL_RenderPresent(game->renderer);
    }

    SDL_Quit();
    return 0;
}
