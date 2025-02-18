#include "tetromino.hpp"
#include "../log.hpp"
#include "tetrominos.hpp"

// Returns a random tetromino
Tetromino Tetromino::RandomTetromino()
{
    int random_number = std::rand() % 7;

    switch (random_number)
    {
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

// Returns true if we can safely move left or right. Returns false otherwise
bool Tetromino::CheckMoveHorizontally(int direction,
                                      Uint8 (&board)[BOARD_HEIGHT][BOARD_WIDTH])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (this->GetShape()[i][j] == 0)
            {
                continue;
            }

            if ((this->position.x + j) + direction < 0 ||
                (this->position.x + j) + direction >= BOARD_WIDTH)
            {
                return false;
            }

            if (board[this->position.y + i]
                     [(this->position.x + j) + direction] > 0)
            {
                return false;
            }
        }
    }
    return true;
}

// Checks if this tetromino is on top of a block or the bottom of the board.
bool Tetromino::CheckIfLanded(Uint8 (&board)[BOARD_HEIGHT][BOARD_WIDTH])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (this->GetShape()[i][j] == 0)
            {
                continue;
            }

            if ((this->position.y + i) + 1 >= BOARD_HEIGHT)
            {
                return true;
            }

            if (board[(this->position.y + i) + 1][this->position.x + j] > 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Returns true if this block can do it's next rotation. returns false
// otherwise.
// Checks every possible rotation besides left and right movement.
// (which doesn't allow wall kicks to work.)
bool Tetromino::CheckValidRotation(Uint8 board[BOARD_HEIGHT][BOARD_WIDTH])
{
    int rotated_block[4][4];
    // Copy the shapes next rotation to a local stack variable for this functions use.
    std::copy(&shapes[(rotation + 1) % 4][0][0],
              &shapes[(rotation + 1) % 4][0][0] + 4 * 4, &rotated_block[0][0]);

    Vector2 pos = this->position;

    for (int offset_y = 0; offset_y <= 4; offset_y++)
    {
        bool valid = true;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (rotated_block[i][j] == 0)
                {
                    continue;
                }
                if ((pos.x + j) < 0 || (pos.x + j) >= BOARD_WIDTH ||
                    (pos.y + i - offset_y) >= BOARD_HEIGHT)
                {
                    valid = false;
                    break;
                }

                if (board[pos.y + i - offset_y][(pos.x + j)] > 0)
                {
                    valid = false;
                    break;
                }
                if (!valid)
                {
                    break;
                }
            }
        }
        if (valid)
        {
            this->position.y -= offset_y;
            return true;
        }
    }
    return false;
}

void Tetromino::RotateClockwise(Uint8 board[BOARD_HEIGHT][BOARD_WIDTH])
{
    if (!this->CheckValidRotation(board))
    {
        return;
    }
    this->rotation = (this->rotation + 1) % 4;
}

void Tetromino::RotateCounterClockwise(Uint8 board[BOARD_HEIGHT][BOARD_WIDTH])
{
    if (!this->CheckValidRotation(board))
    {
        return;
    }
    this->rotation = (this->rotation - 1) % 4;
}

void Tetromino::MoveLeft() { this->position.x--; }

void Tetromino::MoveRight() { this->position.x++; }

void Tetromino::MoveDown() { this->position.y++; }
