#include "tetromino.hpp"
#include "../log.hpp"
#include "tetrominos.hpp"

Tetromino Tetromino::RandomTetromino() {
    return IShape();
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

bool Tetromino::CheckMoveHorizontally(int direction,
                                      int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (this->shape[i][j] == 0) {
                continue;
            }

            if ((this->position.x + j) + direction < 0 ||
                (this->position.x + j) + direction >= BOARD_WIDTH) {
                return false;
            }

            if (board[this->position.y + i]
                     [(this->position.x + j) + direction] > 0) {
                return false;
            }
        }
    }
    return true;
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

#define ROTATION_CENTER_X 1
#define ROTATION_CENTER_Y 1

void Tetromino::RotateClockwise() {
    int temp[4][4] = {0};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (this->shape[i][j] == 0) {
                continue;
            }
            int new_x = -(j - ROTATION_CENTER_Y) + ROTATION_CENTER_X;
            int new_y = (i - ROTATION_CENTER_X) + ROTATION_CENTER_Y;

            if (new_x >= 0 && new_x < 4 && new_y >= 0 && new_y < 4) {
                temp[new_x][new_y] = this->shape[i][j];
            }

            // int new_x = j;
            // int new_y = 3 - i;

            // temp[new_x][new_y] = this->shape[i][j];
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->shape[i][j] = temp[i][j];
        }
    }
}

void Tetromino::RotateCounterClockwise() {
    int temp[4][4] = {0};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int new_x = (j - ROTATION_CENTER_Y) + ROTATION_CENTER_X;
            int new_y = -(i - ROTATION_CENTER_X) + ROTATION_CENTER_Y;

            if (new_x >= 0 && new_x < 4 && new_y >= 0 && new_y < 4) {
                temp[new_x][new_y] = this->shape[i][j];
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->shape[i][j] = temp[i][j];
        }
    }
}

void Tetromino::MoveLeft() { this->position.x--; }

void Tetromino::MoveRight() { this->position.x++; }

void Tetromino::MoveDown() { this->position.y++; }
