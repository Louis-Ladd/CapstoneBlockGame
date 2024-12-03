#pragma once

#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <functional>

#define MAX_KEYS 322

class Game;

class GameEventHandler
{
private:
    bool keys[MAX_KEYS] = {false};
    void UpdatePressedKeys(SDL_Event event);
    std::function<void(SDL_Point)> callback_func = nullptr;

public:
    void SetMouseCallback(const std::function<void(SDL_Point)>& callback_func);
    void HandleEvent(Game* game);
    bool IsKeyDown(SDL_Keycode key);
    bool ResetKey(SDL_Keycode key);
};
