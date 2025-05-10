#pragma once

#include "../utils/vector2.hpp"
#include <SDL2/SDL.h>
#include <algorithm>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

// Tetromino is an example of a abstract class. Tetromino isn't used directly
// (which is why its constructor is protected) as we're meant to use the Shapes
// that inherit from it.
class Tetromino
{
public:
    Vector2 position = {0, 0};
    int shapes[4][4][4];
    int rotation = 0;
    void Render(SDL_Renderer* renderer);
    bool CheckMoveHorizontally(int direction,
                               Uint8 (&board)[BOARD_HEIGHT][BOARD_WIDTH]);
    const int (&GetShape() const)[4][4] { return shapes[rotation]; }
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    bool CheckIfLanded(Uint8 (&board)[BOARD_HEIGHT][BOARD_WIDTH]);
    virtual void RotateClockwise(Uint8 board[BOARD_HEIGHT][BOARD_WIDTH]);
    virtual void RotateCounterClockwise(Uint8 board[BOARD_HEIGHT][BOARD_WIDTH]);
    static Tetromino RandomTetromino();

protected:
    inline bool CheckValidRotation(Uint8 board[BOARD_HEIGHT][BOARD_WIDTH]);
    Tetromino() { memset(shapes, 0, sizeof(shapes)); }

    void SetRotationState(int state, const Uint8 rotation[4][4])
    {
        std::copy(&rotation[0][0], &rotation[0][0] + 4 * 4,
                  &shapes[state][0][0]);
    }
};
