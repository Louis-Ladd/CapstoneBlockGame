#pragma once

#include "../utils/vector2.hpp"
#include <SDL2/SDL.h>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

class Tetromino {
  public:
    Vector2 position = {0, 0};
    int shape[4][4];
    void Render(SDL_Renderer* renderer);
    bool CheckMoveHorizontally(int direction,
                               int board[BOARD_HEIGHT][BOARD_WIDTH]);
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    bool CheckIfLanded(int board[BOARD_HEIGHT][BOARD_WIDTH]);
    void RotateCounterClockwise();
    void RotateClockwise();
    static Tetromino RandomTetromino();

  protected:
    Tetromino() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = 0;
            }
        }
    }
};
