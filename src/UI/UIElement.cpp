#include "UIElement.hpp"
#include "../log.hpp"
#include "SDL_render.h"

void UIElement::Render(SDL_Renderer* renderer)
{
    LOG("Unable to render generic UIElement!");
}

void UIElement::HandleClick(SDL_Point click_point) { return; }
