#pragma once

#include <SDL.h>
#include <iostream>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 600

class Game
{
private:
	bool running = true;
public:
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Event window_event;
	Game(const char *title);
	~Game();
	bool is_running();
	void stop_running();
	void update();
	void render();

};