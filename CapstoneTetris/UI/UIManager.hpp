#pragma once

#include "UIElement.hpp"
#include <SDL.h>
#include <string>
#include <unordered_map>

class UIManager
{
public:
    UIManager(SDL_Renderer* renderer);
    ~UIManager();
    void AddUIElement(std::string name, UIElement* element);
    void RemoveUIElement(int id);
    void Render();
    void InvokeClickEvents(SDL_Point click_point);

private:
    SDL_Renderer* renderer;
    // TODO: TTF Font pointer (I don't have the lib setup yet) TTF_Font* font;
    std::unordered_map<std::string, UIElement*> elements;
};
