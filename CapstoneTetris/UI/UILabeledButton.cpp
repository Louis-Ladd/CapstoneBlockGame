#include "UILabeledButton.hpp"

UILabeledButton::UILabeledButton(int x, int y, int w, int h,
                                 SDL_Color text_color, SDL_Color button_color,
                                 TTF_Font* label_font, SDL_Renderer* renderer,
                                 std::string text)
{
    this->button = new UIButton(x, y, w, h, button_color);
    this->label = new UILabel(x, y, label_font, text, text_color, renderer);

    Vector2 pos = {x, y};
    this->SetPosition(pos);
}

UILabeledButton::~UILabeledButton()
{
    delete this->button;
    delete this->label;
}

void UILabeledButton::Render(SDL_Renderer* renderer)
{
    this->button->Render(renderer);
    this->label->Render(renderer);
}
