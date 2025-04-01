// main.cpp : Defines the entry point for the application.
//
// Author: Louis Harshman 2024
//
// Computer Science CSC1061X00
//
// Build Notes!
// This requires SDL.dll and SDL_ttf.dll on windows
// to be in the same directory as the executable.
// Fonts won't work if "game_over.ttf" isn't in the same directoy that
// you're executing from.
//
// Concepts implemented:
// Abstract Classes (Tetromino, UIElement)
// Polymorphism (UIElement and UIManager)
// Inheritance (Tetrominos, UIElement)
// Map Data Structures (UIManager)
// Matrixies (BlockGame Board, Tetromino.cpp)

#include "blockgame/blockgame.hpp"
#include "mainmenu/mainmenu.hpp"
#include <SDL.h>

int main(int argc, char* argv[])
{
    Application* application = Application::GetInstance();

    RunMainMenu(application);

    BlockGame block_game = BlockGame();

    Uint32 last_frame_time = SDL_GetTicks();

    while (application->GetRunning())
    {

        // Calculates delta time so that we can calculate things independently
        // from the frame rate.
        Uint32 current_frame_time = SDL_GetTicks();
        application->delta_time =
            (current_frame_time - last_frame_time) / 1000.0f;
        last_frame_time = current_frame_time;

        // Background Color
        SDL_SetRenderDrawColor(application->renderer, 0, 0, 128, 0);
        SDL_RenderClear(application->renderer);

        application->event_handler.HandleEvent(application);

        block_game.Update();
        block_game.Render(application->renderer);

        // Flips our double buffer
        SDL_RenderPresent(application->renderer);
    }

    delete application;
    return 0;
}
