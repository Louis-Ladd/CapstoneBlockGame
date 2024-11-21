#include "UIManager.hpp"
#include "../log.hpp"
#include "UIButton.hpp"
#include "UIElement.hpp"
#include "UIRect.hpp"

UIManager::UIManager(SDL_Renderer* renderer) { this->renderer = renderer; }

UIManager::~UIManager()
{
    for (auto& [name, element] : this->elements)
    {
        delete element;
    }
}

void UIManager::AddUIElement(std::string name, UIElement* element)
{
    elements[name] = element;
    return;
}

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
        }
    }
}

void UIManager::Render()
{
    for (auto& [name, element] : this->elements)
    {
        element->Render(renderer);
    }
}
