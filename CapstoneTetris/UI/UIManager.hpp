#pragma once

#include "UIElement.hpp"
#include <SDL.h>
#include <map>

class UIManager
{
  public:
    UIManager(SDL_Renderer* renderer);
    ~UIManager();
    int AddUIElement();
    void RemoveUIElement(int id);
    void UpdateEvents();

  private:
    SDL_Renderer* renderer;
    // TODO: TTF Font pointer (I don't have the lib setup yet) TTF_Font* font;
    std::map<int, UIElement> elements;
};
