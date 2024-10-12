#pragma once

#include "tetromino.h"

class IShape : public Tetromino
{
public:
	IShape() : Tetromino()
	{
		int temp_shape[4][4] = {{0, 1, 0, 0}, 
								{0, 1, 0, 0},
								{0, 1, 0, 0},
								{0, 1, 0, 0}};
		
		std::copy(&temp_shape[0][0], &temp_shape[0][0] + 4 * 4, &shape[0][0]);
	}
};
