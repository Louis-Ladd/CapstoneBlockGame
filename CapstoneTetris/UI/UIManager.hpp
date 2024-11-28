#pragma once

#include "../log.hpp"
#include "UIElement.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

class UIManager
{
private:
    TTF_Font* default_fonts[4];
    SDL_Renderer* renderer;
    std::unordered_map<std::string, UIElement*> elements;

public:
    UIManager(SDL_Renderer* renderer);
    ~UIManager();
    void AddUIElement(std::string name, UIElement* element);
    UIElement* GetUIElement(std::string name) { return this->elements[name]; };
    // void RemoveUIElement(int id);
    void Render();
    void InvokeClickEvents(SDL_Point click_point);
    TTF_Font* GetDefaultFont(int id) const;
};
