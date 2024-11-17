#pragma once

#include "../utils/vector2.hpp"
#include <SDL.h>

class UIElement
{
  public:
    virtual void Render();
    Vector2 GetPosition() const { return this->position; };
    virtual void SetPosition(const Vector2 new_pos)
    {
        this->position = new_pos;
    };

  private:
    Vector2 position = { 0, 0 };
    bool enabled = true;
};
