#pragma once

#include "../UI/UIManager.hpp"
#include "../application.hpp"
#include "../tetromino/tetromino.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <math.h>
#include <queue>

// Standard blockgame board is 10 wide and 20 high
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

enum GameState
{
    Paused,
    Running,
    Lost,
    Quit,
};

class BlockGame
{
private:
    Application* application;
    UIManager ui_manager;
    GameState game_state = Paused;
    // Board is specifically defined as an 8 bit integer to make the board more
    // efficent memory wise.
    Uint8 board[BOARD_HEIGHT][BOARD_WIDTH];
    int score = 0;
    int level = 1;
    int lines = 0;
    double block_drop_grace = 1;
    double block_fall_cooldown = SDL_GetTicks();
    std::queue<Tetromino> block_queue;
    Tetromino current_block = Tetromino::RandomTetromino();
    void SetDrawColor(int block_state, Uint8 tint = 0);
    void UpdateClearedLines();
    void ResetGraceTimer();
    void DropCurrentBlock();
    void UpdateLevel();
    void UpdateScore();
    void ResetBoard();
    void ResetGame();
    void HandleMouseClick(SDL_Point point);
    void SetGameState(GameState new_state) { game_state = new_state; };
    void BuildUI();

public:
    BlockGame();
    void NextBlock();
    void AddBlock(Tetromino tetromino);
    void Update();
    void Render(SDL_Renderer* renderer);
    void SetGameOverUIElements(bool enabled);
    void SetGameUIElements(bool enabled);
    GameState GetGameState() { return game_state; };
    Uint8 (*GetBoard())[BOARD_WIDTH];
};
