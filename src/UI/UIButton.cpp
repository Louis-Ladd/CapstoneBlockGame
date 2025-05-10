#include "UIButton.hpp"
#include "../log.hpp"
#include <SDL2/SDL_rect.h>

void UIButton::SetOnClickFunction(std::function<void(void)> func)
{
    this->on_click = func;
}

void UIButton::HandleClick(SDL_Point click_point)
{
    if (this->enabled)
    {
        this->ExecuteIfClicked(click_point);
    }
}

void UIButton::ExecuteIfClicked(SDL_Point click_point)
{
    if (this->CheckIfPointIn(click_point))
    {
        this->Click();
    }
}

void UIButton::Click() { this->on_click(); }
