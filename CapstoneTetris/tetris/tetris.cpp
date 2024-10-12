#include "tetris.h"
#include <iostream>
Tetris* Tetris::instance_ptr = nullptr;

Tetris::Tetris()
{
	memset(board, 0, sizeof(board));
}

void Tetris::Update()
{
	//TODO: Implement Updating the board state and game flow, etc.
}

#define BLOCK_SIZE 27
#define BLOCK_OFFSET_X 150
#define BLOCK_OFFSET_Y 25

void Tetris::Render(SDL_Renderer* renderer)
{
	SDL_Rect block = { 0, 0, BLOCK_SIZE, BLOCK_SIZE };
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			block.h = BLOCK_SIZE;
			block.w = BLOCK_SIZE;
			switch (this->board[y][x])
			{
				case 0:
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
					break;
				default:
					SDL_GetRenderDrawColor(renderer, 0, 0, 0, 0);
					break;
			}

			block.x = (BLOCK_SIZE * x) + BLOCK_OFFSET_X;
			block.y = (BLOCK_SIZE * y) + BLOCK_OFFSET_Y;
			SDL_RenderFillRect(renderer, &block);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(renderer, &block);
		}
	}
}

int (*Tetris::GetBoard())[BOARD_WIDTH]
{
	return this->board;
}

