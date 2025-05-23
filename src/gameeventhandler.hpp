#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <functional>

#define MAX_KEYS 322

class Application;

class GameEventHandler
{
private:
    bool keys[MAX_KEYS] = {false};
    void UpdatePressedKeys(SDL_Event event);
    // Anything this must set it back to nullptr on cleanup!
    std::function<void(SDL_Point)> callback_func = nullptr;

public:
    void SetMouseCallback(const std::function<void(SDL_Point)>& callback_func);
    void HandleEvent(Application* game);
    bool IsKeyDown(SDL_Keycode key);
    bool ResetKey(SDL_Keycode key);
};
