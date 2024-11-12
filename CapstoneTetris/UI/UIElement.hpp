#pragma once

#include "../utils/vector2.hpp"
#include <SDL.h>

class UIElement
{
  public:
    void Render();
    Vector2 GetPosition() { return this->position; };
    virtual void SetPosition(const Vector2 new_pos)
    {
        this->position = new_pos;
    };

  private:
    Vector2 position;
};
