#pragma once

#include <SDL.h>
#include <string>
#include "../utils/vector2.h"

class Tetromino
{
private:
	Vector2 position = { 0, 0 };
public:
	int shape[4][4];
	void Render(SDL_Renderer* renderer);
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	bool CheckIfAtBottom();
	void RotateCounterClockWise();
	void RotateClockwise();
	static Tetromino RandomTetromino();
protected:
	Tetromino()
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				shape[i][j] = 0;			
			}
		}
	}
};