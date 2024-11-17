#pragma once

#include "UIElement.hpp"
#include <SDL.h>
#include <unordered_map>
#include <string>

class UIManager
{
  public:
    UIManager(SDL_Renderer* renderer);
    void AddUIElement(std::string name, UIElement element);
    void RemoveUIElement(int id);
    void Render();
  private:
    SDL_Renderer* renderer;
    // TODO: TTF Font pointer (I don't have the lib setup yet) TTF_Font* font;
    std::unordered_map<std::string, UIElement> elements;
};
