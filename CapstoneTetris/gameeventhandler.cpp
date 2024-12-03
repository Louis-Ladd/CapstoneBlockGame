#include "gameeventhandler.hpp"
#include "game.hpp"
#include <SDL_keycode.h>

void GameEventHandler::SetMouseCallback(
    const std::function<void(SDL_Point)>& callback_func)
{
    this->callback_func = callback_func;
}

void GameEventHandler::UpdatePressedKeys(SDL_Event event)
{
    int keycode = event.key.keysym.sym;

    if (keycode < 0 || keycode > MAX_KEYS)
    {
        return;
    }

    switch (event.type)
    {
        case SDL_KEYDOWN:
            this->keys[keycode] = true;
            break;
        case SDL_KEYUP:
            this->keys[keycode] = false;
            break;
    }
}

bool GameEventHandler::IsKeyDown(SDL_Keycode keycode) { return keys[keycode]; }

bool GameEventHandler::ResetKey(SDL_Keycode keycode)
{
    if (IsKeyDown(keycode))
    {
        keys[keycode] = false;
        return true;
    }
    return false;
}

// Handles all SDL window events
void GameEventHandler::HandleEvent(Game* game)
{
    while (SDL_PollEvent(&game->window_event) > 0)
    {
        switch (game->window_event.type)
        {
            case SDL_QUIT:
                game->Quit();
                break;
            case SDL_KEYDOWN:
                this->UpdatePressedKeys(game->window_event);
                break;
            case SDL_KEYUP:
                this->UpdatePressedKeys(game->window_event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (!callback_func)
                {
                    return;
                }
                SDL_Point mouse_pos = {game->window_event.motion.x,
                                       game->window_event.motion.y};
                this->callback_func(mouse_pos);
                break;
        }
    }
}
