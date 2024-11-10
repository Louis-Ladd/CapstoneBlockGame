// main.cpp : Defines the entry point for the application.
//

#include "main.hpp"

int main(int argc, char* argv[]) {
    std::cout << "Game starting..." << std::endl;

    Game* game = Game::GetInstance();
    Tetris* tetris = Tetris::GetInstance();

    Uint32 last_frame_time = SDL_GetTicks();

    while (game->GetRunning()) {

        Uint32 current_frame_time = SDL_GetTicks();
        game->delta_time = (current_frame_time - last_frame_time) / 1000.0f;
        last_frame_time = current_frame_time;

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
