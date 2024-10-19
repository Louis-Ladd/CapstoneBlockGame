#include "tetris.h"
#include <iostream>
Tetris* Tetris::instance_ptr = nullptr;

#define BLOCK_SIZE 27
#define BLOCK_OFFSET_X 150
#define BLOCK_OFFSET_Y 25

Tetris::Tetris()
{
	for (int i = 0; i < 3; i++)
	{
		this->block_queue.push(Tetromino::RandomTetromino());
	}

	this->NextBlock(); 

	memset(board, 0, sizeof(board));
}

void Tetris::NextBlock()
{
	if (current_block != nullptr)
	{ delete current_block; }

	current_block = block_queue.front();
	block_queue.pop();
	block_queue.push(Tetromino::RandomTetromino());

	current_block->position.x = 3;
}



void Tetris::SetDrawColor(int block_state, SDL_Renderer* renderer)
{
	switch (block_state)
	{
		case 0:
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Black
			break;
		case 1:
			SDL_SetRenderDrawColor(renderer, 0, 255, 240, 0); // Cyan 
			break;
		case 2:
			SDL_SetRenderDrawColor(renderer, 175, 0, 239, 0); // Purple
			break;
		case 3:
			SDL_SetRenderDrawColor(renderer, 255, 188, 0, 0); // Orange
			break;
		case 4:
			SDL_SetRenderDrawColor(renderer, 0, 111, 255, 0); // Blue
			break;
		case 5:
			SDL_SetRenderDrawColor(renderer, 0, 245, 41, 0); // Green
			break;
		case 6:
			SDL_SetRenderDrawColor(renderer, 238, 0, 24, 0); //Red
			break;
		case 7:
			SDL_SetRenderDrawColor(renderer, 246, 246, 0, 0); // Yellow
			break;
		default:
			SDL_GetRenderDrawColor(renderer, 0, 0, 0, 0);
			break;
	}
}

void Tetris::Update()
{
}

void Tetris::Render(SDL_Renderer* renderer)
{
	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << current_block->shape[j][i];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;*/

	SDL_Rect block = { 0, 0, BLOCK_SIZE, BLOCK_SIZE };

	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			SetDrawColor(this->board[y][x], renderer);

			block.x = (BLOCK_SIZE * x) + BLOCK_OFFSET_X;
			block.y = (BLOCK_SIZE * y) + BLOCK_OFFSET_Y;
			SDL_RenderFillRect(renderer, &block);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(renderer, &block);
		}
	}

	for (int ix = 0; ix < 4; ix++)
	{
		for (int iy = 0; iy < 4; iy++)
		{
			if (this->current_block->shape[iy][ix] == 0)
			{ continue; }

			SetDrawColor(this->current_block->shape[iy][ix], renderer);
			block.x = (BLOCK_SIZE * ix) + BLOCK_OFFSET_X + this->current_block->position.x * BLOCK_SIZE;
			block.y = (BLOCK_SIZE * iy) + BLOCK_OFFSET_Y + this->current_block->position.y * BLOCK_SIZE;
			SDL_RenderFillRect(renderer, &block);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(renderer, &block);
		}
	}

	Tetromino* next_block = this->block_queue.front();

	for (int ix = 0; ix < 4; ix++)
	{
		for (int iy = 0; iy < 4; iy++)
		{
			if (this->block_queue.front()->shape[iy][ix] == 0)
			{ continue; }
			
			SetDrawColor(next_block->shape[iy][ix], renderer);
			block.x = (BLOCK_SIZE * ix) + 600;
			block.y = (BLOCK_SIZE * iy) + 40;
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

