#pragma once

#include "UIButton.hpp"
#include "UIElement.hpp"
#include "UILabel.hpp"

class UILabeledButton : public UIElement
{
public:
    UIElementType GetType() const override
    {
        return UIElementType::LabeledButton;
    };
    UILabeledButton(int x, int y, int w, int h, SDL_Color text_color,
                    SDL_Color button_color, TTF_Font* label_font,
                    SDL_Renderer* renderer, std::string text);
    UILabeledButton(int x, int y, int w, int h, SDL_Color text_color,
                    SDL_Color button_color, TTF_Font* label_font,
                    SDL_Renderer* renderer, std::string text,
                    std::function<void(void)> func)
        : UILabeledButton(x, y, w, h, text_color, button_color, label_font,
                          renderer, text)
    {
        this->button->SetOnClickFunction(func);
    };
    ~UILabeledButton() override;
    void SetPosition(const Vector2 new_pos) override
    {
        button->SetPosition(new_pos);
        // BUG: Center text on button
        label->SetPosition(new_pos);
    }
    void SetEnabled(bool new_value) { enabled = new_value; };
    void Render(SDL_Renderer* renderer) override;
    UIButton* button;
    UILabel* label;
};
