#pragma once

#include "../utils/vector2.hpp"
#include <SDL.h>

enum class UIElementType
{
    GenericElement,
    Rect,
    Button,
    Label,
    LabeledButton,
};

// The UIElement class uses polymorphism so that all UI elements can be
// genericly handled in the UIManager.
class UIElement
{
public:
    virtual UIElementType GetType() const
    {
        return UIElementType::GenericElement;
    };
    virtual ~UIElement() {};
    virtual void HandleClick(SDL_Point click_point);
    virtual void Render(SDL_Renderer* renderer);
    Vector2 GetPosition() const { return this->position; };
    virtual void SetPosition(const Vector2 new_pos) { position = new_pos; };
    virtual void SetEnabled(bool new_value) { enabled = new_value; };
    bool GetEnabled() { return enabled; }

protected:
    Vector2 position = {0, 0};
    bool enabled = true;
};
