#include "tetromino.hpp"
#include "tetrominos.hpp"

Tetromino Tetromino::RandomTetromino() {
    int random_number = std::rand() % 7;

    switch (random_number) {
        case 0:
            return IShape();
            break;
        case 1:
            return TShape();
            break;
        case 2:
            return LShape();
            break;
        case 3:
            return JShape();
            break;
        case 4:
            return SShape();
            break;
        case 5:
            return ZShape();
            break;
        case 6:
            return OShape();
            break;
    }
    return IShape();
}

bool Tetromino::CheckIfLanded(int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (this->shape[i][j] == 0) {
                continue;
            }

            if ((this->position.y + i) + 1 >= BOARD_HEIGHT) {
                return true;
            }

            if (board[(this->position.y + i) + 1][this->position.x + j] > 0) {
                return true;
            }
        }
    }
    return false;
}

void Tetromino::MoveDown() { this->position.y++; }
