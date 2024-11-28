#include "UILabel.hpp"

UILabel::UILabel(int x, int y, TTF_Font* font, std::string text,
                 SDL_Color color, SDL_Renderer* renderer)
{
    this->position.x = x;
    this->position.y = y;
    this->font = font;
    this->text = text;
    this->color = color;

    this->RedrawTexture(renderer);
}

UILabel::~UILabel() { SDL_DestroyTexture(this->texture); }

void UILabel::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
}

void UILabel::RedrawTexture(SDL_Renderer* renderer)
{
    this->surface = TTF_RenderText_Solid(font, text.c_str(), color);

    SDL_Rect label_rect = {this->position.x, this->position.y, this->surface->w,
                           this->surface->h};
    this->rect = label_rect;

    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
}
