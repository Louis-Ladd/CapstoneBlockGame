#include "UIManager.hpp"
#include "../log.hpp"
#include "UIButton.hpp"
#include "UIElement.hpp"
#include "UILabeledButton.hpp"
#include "UIRect.hpp"

UIManager::UIManager(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->default_fonts[0] = TTF_OpenFont("game_over.ttf", 24);
    this->default_fonts[1] = TTF_OpenFont("game_over.ttf", 32);
    this->default_fonts[2] = TTF_OpenFont("game_over.ttf", 64);
    this->default_fonts[3] = TTF_OpenFont("game_over.ttf", 128);
}

UIManager::~UIManager()
{
    for (int i = 0; i < 4; i++)
    {
        if (default_fonts[i])
        {
            TTF_CloseFont(default_fonts[i]);
        }
    }

    for (auto& [name, element] : this->elements)
    {
        delete element;
    }
    this->elements.clear();

    this->renderer = nullptr;
}

void UIManager::AddUIElement(std::string name, UIElement* element)
{
    elements[name] = element;
    return;
}

// Check if an element has been clicked. If so, handle their unique behavior.
void UIManager::InvokeClickEvents(SDL_Point mouse_point)
{
    for (auto& [name, element] : this->elements)
    {
        switch (element->GetType())
        {
            case UIElementType::Rect:
            {
                UIRect* rect = dynamic_cast<UIRect*>(element);
                if (rect->CheckIfPointIn(mouse_point))
                    LOG("Is rect");
                break;
            }
            case UIElementType::LabeledButton:
            {
                UILabeledButton* labeled_button =
                    dynamic_cast<UILabeledButton*>(element);
                if (labeled_button->button->CheckIfPointIn(mouse_point))
                {
                    labeled_button->button->ExecuteIfClicked(mouse_point);
                }
                break;
            }
            case UIElementType::Button:
            {
                UIButton* button = dynamic_cast<UIButton*>(element);
                if (button->CheckIfPointIn(mouse_point))
                {
                    LOG("Button pressed, executing callback...");
                    button->ExecuteIfClicked(mouse_point);
                }
                break;
            }
            case UIElementType::GenericElement:
            {
                LOG("GenericElement not implemented...");
                break;
            }

            default:
            {
                // Just do nothing
                break;
            }
        }
    }
}

void UIManager::Render()
{
    // This is polymorphism at work, all UIElements need to be rendered but we
    // don't care about that. We just need to render them and the elements will
    // change behavior as needed.
    for (auto& [name, element] : this->elements)
    {
        element->Render(renderer);
    }
}

TTF_Font* UIManager::GetDefaultFont(int id) const
{
    if (id >= 4)
    {
        return nullptr;
    }

    return this->default_fonts[id];
}
