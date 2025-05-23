#pragma once

#include "UIRect.hpp"
#include <SDL2/SDL.h>
#include <functional>

class UIButton : public UIRect
{
private:
    std::function<void(void)> on_click = nullptr;

public:
    UIElementType GetType() const override { return UIElementType::Button; };
    UIButton(int x, int y, int w, int h) : UIRect(x, y, w, h) {};
    UIButton(int x, int y, int w, int h, SDL_Color color) : UIButton(x, y, w, h)
    {
        SetColor(color);
    };
    UIButton(int x, int y, int w, int h, std::function<void(void)> func)
        : UIButton(x, y, w, h)
    {
        on_click = func;
    };
    void SetOnClickFunction(std::function<void(void)> func);
    void ExecuteIfClicked(SDL_Point point);
    void Click();
    void HandleClick(SDL_Point click_point) override;
};
