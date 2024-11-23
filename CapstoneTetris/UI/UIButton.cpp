#include "UIButton.hpp"
#include "../log.hpp"

void UIButton::SetOnClickFunction(std::function<void(void)> func)
{
    this->on_click = func;
}

void UIButton::ExecuteIfClicked(SDL_Point click_point)
{
    if (this->CheckIfPointIn(click_point))
    {
        this->Click();
    }
}

void UIButton::Click()
{
    this->on_click();
}

