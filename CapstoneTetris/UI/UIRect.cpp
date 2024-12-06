#include "UIRect.hpp"

UIRect::UIRect(int x, int y, int w, int h)
{
    this->position.x = x;
    this->position.y = y;
    this->rect = {this->position.x, this->position.y, w, h};
}

bool UIRect::CheckIfPointIn(SDL_Point point)
{
    return SDL_PointInRect(&point, &this->rect);
}

void UIRect::SetPosition(const Vector2 new_pos)
{
    this->rect.x = new_pos.x;
    this->rect.y = new_pos.y;
    this->position = new_pos;
}

void UIRect::Render(SDL_Renderer* renderer)
{
    if (!this->enabled)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g,
                           this->color.b, this->color.a);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    // Always set color to black when done drawing.
    return;
}
