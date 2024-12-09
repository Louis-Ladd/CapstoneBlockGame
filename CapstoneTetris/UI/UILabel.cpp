#include "UILabel.hpp"
#include "SDL_render.h"
#include "SDL_surface.h"

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

// We have ownership of SDL textures and surfaces so we must free them.
UILabel::~UILabel()
{
    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
    if (this->surface != nullptr)
    {
        SDL_FreeSurface(this->surface);
        this->texture = nullptr;
    }
}

void UILabel::Render(SDL_Renderer* renderer)
{
    if (!this->enabled)
    {
        return;
    }
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
}

// Redraws the labels texture. This is required with ANY MODIFICATIONS. This is
// because UI label is just a texture and we draw that texture every frame.
// Thus, the texture has to be redrawn
void UILabel::RedrawTexture(SDL_Renderer* renderer)
{
    if (this->surface != nullptr)
    {
        SDL_FreeSurface(this->surface);
        this->surface = nullptr;
    }

    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
        this->surface = nullptr;
    }

    this->surface = TTF_RenderText_Solid(font, text.c_str(), color);

    SDL_Rect label_rect = {this->position.x, this->position.y, this->surface->w,
                           this->surface->h};
    this->rect = label_rect;

    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
}
