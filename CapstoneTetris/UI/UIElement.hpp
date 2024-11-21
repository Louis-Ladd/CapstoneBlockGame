#pragma once

#include "../utils/vector2.hpp"
#include <SDL.h>

enum class UIElementType
{
    GenericElement,
    Rect,
    Button
};

class UIElement
{
public:
    virtual UIElementType GetType() const
    {
        return UIElementType::GenericElement;
    };
    virtual void Render(SDL_Renderer* renderer);
    Vector2 GetPosition() const { return this->position; };
    virtual void SetPosition(const Vector2 new_pos)
    {
        this->position = new_pos;
    };

protected:
    Vector2 position = {0, 0};
    bool enabled = true;
};
