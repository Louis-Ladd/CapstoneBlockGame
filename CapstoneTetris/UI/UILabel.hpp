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
	UILabel(int x, int y, TTF_Font* font, std::string text, SDL_Color color, SDL_Renderer* renderer);
	~UILabel();
	void Render(SDL_Renderer* renderer) override;
	void SetText(std::string new_text) { text = new_text; };
};
