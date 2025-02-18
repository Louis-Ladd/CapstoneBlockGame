#pragma once

#include "UIElement.hpp"
#include <SDL.h>

class UIRect : public UIElement
{
private:
    SDL_Rect rect;
    SDL_Color color;

public:
    UIRect() {};
    UIRect(int x, int y, int w, int h);
    UIRect(int x, int y, int w, int h, SDL_Color color) : UIRect(x, y, w, h)
    {
        this->color = color;
    }
    UIElementType GetType() const override { return UIElementType::Rect; };
    bool CheckIfPointIn(SDL_Point point);
    void SetPosition(const Vector2 new_pos) override;
    void SetSize(int w, int h)
    {
        this->rect.w = w;
        this->rect.h = h;
    };
    void SetColor(SDL_Color color) { this->color = color; };
    void Render(SDL_Renderer* renderer) override;
    void HandleClick(SDL_Point click_point) override { return; };
};
