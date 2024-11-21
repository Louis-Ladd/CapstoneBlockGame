#include "UIButton.hpp"
#include "../log.hpp"

void UIButton::ExecuteIfClicked(SDL_Point click_point)
{
    LOG("Executing if clicked...");
    if (this->CheckIfPointIn(click_point))
    {
        this->on_click();
    }
}

void UIButton::SetOnClickFunction(std::function<void(void)> func)
{
    this->on_click = func;
}
