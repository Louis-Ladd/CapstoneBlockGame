#include "UIManager.hpp"
#include "UIElement.hpp"

UIManager::UIManager(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}


void UIManager::AddUIElement(std::string name, UIElement element)
{
	elements[name] = element;
	return;
}

void UIManager::Render()
{
	for (auto& [name, element] : this->elements)
	{
		element.Render();
	}
}
