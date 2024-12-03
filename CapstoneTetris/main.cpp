// main.cpp : Defines the entry point for the application.
//
// Build Notes!
// This requires SDL.dll and SDL_ttf.dll on windows
// to be in the same directory as the executable.
// Fonts won't work if "game_over.ttf" isn't in the same directoy that you're
// executing from.

// Concepts implemented:
// Abstract Classes (Tetromino, UIElement)
// Polymorphism (UIElement and UIManager)
// Inheritance (Tetrominos, UIElement)
// Map Data Structures

#include "main.hpp"

int main(int argc, char* argv[])
{
    Game* game = Game::GetInstance();

    RunMainMenu(game->renderer, game);

    Tetris* tetris = Tetris::GetInstance();

    Uint32 last_frame_time = SDL_GetTicks();

    while (game->GetRunning())
    {

        // Calculates delta time so that we can calculate indepenantly from the
        // frame rate.
        Uint32 current_frame_time = SDL_GetTicks();
        game->delta_time = (current_frame_time - last_frame_time) / 1000.0f;
        last_frame_time = current_frame_time;

        // Background Color
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 128, 0);
        SDL_RenderClear(game->renderer);

        game->event_handler.HandleEvent(game);

        tetris->Update();
        tetris->Render(game->renderer);

        // Flips our double buffer
        SDL_RenderPresent(game->renderer);
    }

    delete game;
    delete tetris;
    return 0;
}
