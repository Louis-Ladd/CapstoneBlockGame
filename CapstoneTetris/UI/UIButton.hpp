#pragma once

#include "UIRect.hpp"
#include <SDL.h>
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
        this->SetColor(color);
    };
    UIButton(int x, int y, int w, int h, std::function<void(void)> func) : UIButton(x, y, w, h)
    {
        this->on_click = func;
    };
    void SetOnClickFunction(std::function<void(void)> func);
    void ExecuteIfClicked(SDL_Point point);
    void Click();
};
