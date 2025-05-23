#include "UIManager.hpp"
#include "../application.hpp"
#include "../log.hpp"

// Sets up all default fonts so the UI elements can access them
UIManager::UIManager(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->default_fonts[0] = TTF_OpenFont("game_over.ttf", 24);
    if (this->default_fonts[0] == nullptr)
    {
        LOG("Unable to find game_over.ttf");
        Application::GetInstance()->Quit();
        return;
    }
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
        if (element != nullptr)
        {
            delete element;
        }
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
        if (!element->GetEnabled())
        {
            continue;
        }
        element->HandleClick(mouse_point);
    }
}

void UIManager::Render()
{
    // This is polymorphism at work, all UIElements need to be rendered
    // differently but we don't care about that. We just need to render them and
    // the elements will change behavior as needed.
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
