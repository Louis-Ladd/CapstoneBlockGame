#include "tetromino.h"
#include "tetrominos.h"

#include <iostream>

Tetromino* Tetromino::RandomTetromino()
{
	int random_number = std::rand() % 7;

	std::cout << random_number << std::endl;

	switch (random_number)
	{
		case 0:
			return new IShape();
			break;
		case 1:
			return new TShape();
			break;
		case 2:
			return new LShape();
			break;
		case 3:
			return new JShape();
			break;
		case 4:
			return new SShape();
			break;
		case 5: 
			return new ZShape();
			break;
		case 6:
			return new OShape();
			break;
	}
}
