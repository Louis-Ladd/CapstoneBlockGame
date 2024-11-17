#include "mainmenu.hpp"
#include "../log.hpp"

MainMenu::~MainMenu()
{
	this->game->event_handler.SetMouseCallback(nullptr);
}

void MainMenu::BuildMainMenu()
{
	this->game->event_handler.SetMouseCallback([this](SDL_Point point)
		{
			HandleMouseClick(point);
		});
}

void MainMenu::HandleMouseClick(SDL_Point point)
{
	LOG("Click at: x:%i y:%i", point.x, point.y);
}

void MainMenu::Start()
{
	BuildMainMenu();
	while (game->GetRunning())
	{
		this->game->event_handler.HandleEvent(this->game);
		this->ui_manager.Render();

		if (this->game->event_handler.IsKeyDown(SDLK_x))
		{
			break;
		}
	}
}