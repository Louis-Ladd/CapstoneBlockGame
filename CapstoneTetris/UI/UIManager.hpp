#pragma once

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
    // This Map is an example of a data structure I learned about in this
    // course. I used a unordered map since order doesn't matter and I don't
    // want the overhead of a tree structure that std::map uses.
    // std::unordered_map uses a hash table.
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
