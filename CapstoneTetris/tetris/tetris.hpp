#pragma once

#include "../game.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetrominos.hpp"
#include <SDL_keycode.h>
#include <SDL_timer.h>
#include <SDL.h>
#include <queue>
#include <stdlib.h>
#include <vector>

// Standard tetris is 10 wide and 20 high
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

enum GAME_STATES { paused, running, end };

class Tetris {
  private:
    Tetris();
    static Tetris* instance_ptr;
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    double block_fall_cooldown = SDL_GetTicks();
    std::queue<Tetromino> block_queue;
    Game* game;
    Tetromino current_block = Tetromino::RandomTetromino();
    void SetDrawColor(int block_state, SDL_Renderer* renderer);
    void UpdateClearedLines();

  public:
    // Singleton
    static Tetris* GetInstance() {
        if (instance_ptr == nullptr) {
            instance_ptr = new Tetris();
        }

        return instance_ptr;
    }
    ~Tetris();
    void NextBlock();
    void AddBlock(Tetromino tetromino);
    void Update();
    void Render(SDL_Renderer* renderer);
    int (*GetBoard())[BOARD_WIDTH];
};
