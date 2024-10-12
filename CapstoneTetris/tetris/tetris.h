#pragma once

#include <queue>
#include "../tetromino/tetromino.h"

// Standard tetris is 10 wide and 20 high
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

enum GAME_STATES
{
	paused,
	running,
	end
};

class Tetris
{
private:
	static Tetris* instance_ptr;
	int board[BOARD_HEIGHT][BOARD_WIDTH]; 	
	std::queue<Tetromino> block_queue;
	Tetromino* current_block;
	Tetris();
public:
	// Singleton
	static Tetris* GetInstance()
	{
		if (instance_ptr == nullptr)
		{
			instance_ptr = new Tetris();
		}

		return instance_ptr;
	}
	~Tetris(); 
	void Update();
	void Render(SDL_Renderer* renderer);
	int (*GetBoard())[BOARD_WIDTH];
};

