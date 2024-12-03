#pragma once

#include "UIElement.hpp"
#include <SDL_ttf.h>
#include <string>

class UILabel : public UIElement
{
private:
    std::string text = "";
    SDL_Color color;
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;

public:
    UIElementType GetType() const override { return UIElementType::Label; };
    UILabel(int x, int y, TTF_Font* font, std::string text, SDL_Color color,
            SDL_Renderer* renderer);
    ~UILabel() override;
    void Render(SDL_Renderer* renderer) override;
    void RedrawTexture(SDL_Renderer* renderer);
    void SetText(SDL_Renderer* renderer, std::string new_text)
    {
        text = new_text;
        this->RedrawTexture(renderer);
    };
};
