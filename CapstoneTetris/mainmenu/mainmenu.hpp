#pragma once

#include <SDL.h>
#include "../UI/UIManager.hpp"
#include "../game.hpp"

class MainMenu
{
private:
	Game* game;
	SDL_Renderer* renderer;
	UIManager ui_manager;
	void BuildMainMenu();
public:
	~MainMenu();
	void HandleMouseClick(SDL_Point point);
	MainMenu(SDL_Renderer* renderer, Game* game) : game(game), renderer(renderer), ui_manager(renderer) {};
	void Start();
};