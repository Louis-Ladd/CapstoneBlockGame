#pragma once

#include "../utils/vector2.hpp"
#include <SDL.h>
#include <algorithm>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

class Tetromino
{
  public:
    Vector2 position = {0, 0};
    int shapes[4][4][4];
    int rotation = 0;
    void Render(SDL_Renderer* renderer);
    bool CheckMoveHorizontally(int direction,
                               int (&board)[BOARD_HEIGHT][BOARD_WIDTH]);
    const int (&GetShape() const)[4][4] { return shapes[rotation]; }
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    bool CheckIfLanded(int (&board)[BOARD_HEIGHT][BOARD_WIDTH]);
    void RotateCounterClockwise();
    void RotateClockwise();
    static Tetromino RandomTetromino();

  protected:
    Tetromino()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int r = 0; r < 4; r++)
                {
                    shapes[r][i][j] = 0;
                }
            }
        }
    }

    void SetRotationState(int state, const int rotation[4][4])
    {
        std::copy(&rotation[0][0], &rotation[0][0] + 4 * 4,
                  &shapes[state][0][0]);
    }
};
