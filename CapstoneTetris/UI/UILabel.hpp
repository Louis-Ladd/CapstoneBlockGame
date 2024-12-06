#pragma once

#include "UIElement.hpp"
#include <SDL_ttf.h>
#include <string>

class UILabel : public UIElement
{
private:
    std::string text = "";
    SDL_Color color;
    TTF_Font* font = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;

public:
    UIElementType GetType() const override { return UIElementType::Label; };
    UILabel(int x, int y, TTF_Font* font, std::string text, SDL_Color color,
            SDL_Renderer* renderer);
    ~UILabel() override;
    void Render(SDL_Renderer* renderer) override;
    void SetPosition(const Vector2 new_pos) override
    {
        position = new_pos;
        rect.x = new_pos.x;
        rect.y = new_pos.y;
    }
    void RedrawTexture(SDL_Renderer* renderer);
    void SetText(SDL_Renderer* renderer, std::string new_text)
    {
        text = new_text;
        this->RedrawTexture(renderer);
    };
    void HandleClick(SDL_Point click_point) override { return; };
    int GetTextWidth() { return surface->w; };
};
