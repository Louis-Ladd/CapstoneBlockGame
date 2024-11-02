#include "input.hpp"
#include "game.hpp"
#include <SDL2/SDL_keycode.h>

void GameEventHandler::UpdatePressedKeys(SDL_Event event) {
    int keycode = event.key.keysym.sym;

    if (keycode < 0 || keycode > MAX_KEYS) {
        return;
    }

    switch (event.type) {
        case SDL_KEYDOWN:
            this->keys[keycode] = true;
            break;
        case SDL_KEYUP:
            this->keys[keycode] = false;
            break;
    }
}

bool GameEventHandler::IsKeyDown(SDL_Keycode keycode) { return keys[keycode]; }

bool GameEventHandler::ResetKey(SDL_Keycode keycode) {
    if (IsKeyDown(keycode)) {
        keys[keycode] = false;
        return true;
    }
    return false;
}

void GameEventHandler::HandleEvent(Game* game) {
    while (SDL_PollEvent(&game->window_event) > 0) {
        switch (game->window_event.type) {
            case SDL_QUIT:
                game->SetRunning(false);
                break;
            case SDL_KEYDOWN ... SDL_KEYUP:
                this->UpdatePressedKeys(game->window_event);
                break;
        }
    }
}
