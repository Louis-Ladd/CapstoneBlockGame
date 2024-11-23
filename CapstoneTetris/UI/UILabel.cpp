#include "UILabel.hpp"

UILabel::UILabel(int x, int y, TTF_Font* font, std::string text, SDL_Color color, SDL_Renderer* renderer)
{
	this->position.x = x;
	this->position.y = y;
	this->font = font;
	this->text = text;
	this->color = color;

	this->surface = TTF_RenderText_Solid(font, text.c_str(), color);

	SDL_Rect label_rect = { x, y, this->surface->w, this->surface->h };
	this->rect = label_rect;

	this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
}

UILabel::~UILabel()
{
	SDL_DestroyTexture(this->texture);
}

void UILabel::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
}