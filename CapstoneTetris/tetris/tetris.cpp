#include "tetris.hpp"
#include "../log.hpp"
#include <iostream>

Tetris* Tetris::instance_ptr = nullptr;

#define BLOCK_SIZE 27
#define BLOCK_OFFSET_X 150
#define BLOCK_OFFSET_Y 25

Tetris::Tetris()
{
    block_queue.push(TShape());
    for (int i = 0; i < 3; i++)
    {
        this->block_queue.push(Tetromino::RandomTetromino());
    }

    this->NextBlock();

    memset(board, 0, sizeof(board));

    this->game = Game::GetInstance();

    if (this->game == nullptr)
    {
        LOG("Tetris couldn't find game insance");
    }
}

void Tetris::SetDrawColor(int block_state)
{
    SDL_Renderer* renderer = this->game->renderer;
    switch (block_state)
    {
        case 0:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Black
            break;
        case 1:
            SDL_SetRenderDrawColor(renderer, 0, 255, 240, 0); // Cyan
            break;
        case 2:
            SDL_SetRenderDrawColor(renderer, 175, 0, 239, 0); // Purple
            break;
        case 3:
            SDL_SetRenderDrawColor(renderer, 255, 188, 0, 0); // Orange
            break;
        case 4:
            SDL_SetRenderDrawColor(renderer, 0, 111, 255, 0); // Blue
            break;
        case 5:
            SDL_SetRenderDrawColor(renderer, 0, 245, 41, 0); // Green
            break;
        case 6:
            SDL_SetRenderDrawColor(renderer, 238, 0, 24, 0); // Red
            break;
        case 7:
            SDL_SetRenderDrawColor(renderer, 246, 246, 0, 0); // Yellow
            break;
        default:
            SDL_GetRenderDrawColor(renderer, 0, 0, 0, 0);
            break;
    }
}

void Tetris::ResetGraceTimer() { this->block_drop_grace = 0.5f + level / 4.0f; }

void Tetris::DropCurrentBlock()
{
    this->AddBlock(this->current_block);
    this->NextBlock();
    this->UpdateClearedLines();
    ResetGraceTimer();
}

void Tetris::Update()
{
    LOG("Level: %i Score: %i", this->level, this->score);
    if (SDL_GetTicks() - this->block_fall_cooldown >= (200 - pow(level, 2)) &&
        !this->current_block.CheckIfLanded(this->board))
    {
        this->current_block.MoveDown();
        this->block_fall_cooldown = SDL_GetTicks();
        ResetGraceTimer();
    }

    if (this->current_block.CheckIfLanded(this->board))
    {
        if (this->block_drop_grace >= 0)
        {
            this->block_drop_grace -= 0.5f * this->game->delta_time;
        }
        else
        {
            this->DropCurrentBlock();
        }
    }

    if (this->game->event_handler.ResetKey(SDLK_a) &&
        this->current_block.CheckMoveHorizontally(-1, board))
    {
        this->current_block.MoveLeft();
    }
    if (this->game->event_handler.ResetKey(SDLK_d) &&
        this->current_block.CheckMoveHorizontally(1, board))
    {
        this->current_block.MoveRight();
    }

    if (this->game->event_handler.ResetKey(SDLK_w))
    {
        this->current_block.RotateClockwise(board);
    }
    if (this->game->event_handler.ResetKey(SDLK_s) &&
        !this->current_block.CheckIfLanded(board))
    {
        this->current_block.position.y++;
    }
    if (this->game->event_handler.ResetKey(SDLK_SPACE))
    {
        while (!this->current_block.CheckIfLanded(board))
        {
            this->current_block.position.y++;
        }
        DropCurrentBlock();
    }
}

void Tetris::Render(SDL_Renderer* renderer)
{
    // Draw game elements
    SDL_Rect block = {BLOCK_OFFSET_X, BLOCK_OFFSET_Y, BOARD_WIDTH * BLOCK_SIZE,
                      BOARD_HEIGHT * BLOCK_SIZE};

    SetDrawColor(0);
    SDL_RenderFillRect(renderer, &block);

    block.x = 600;
    block.y = 40;
    block.w = BLOCK_SIZE * 4;
    block.h = BLOCK_SIZE * 4;

    SetDrawColor(0);
    SDL_RenderFillRect(renderer, &block);

    block.w = BLOCK_SIZE;
    block.h = BLOCK_SIZE;

    // Draw Tetrominos

    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        for (int y = 0; y < BOARD_HEIGHT; y++)
        {
            if (this->board[y][x] == 0)
            {
                continue;
            }

            SetDrawColor(this->board[y][x]);

            block.x = (BLOCK_SIZE * x) + BLOCK_OFFSET_X;
            block.y = (BLOCK_SIZE * y) + BLOCK_OFFSET_Y;
            SDL_RenderFillRect(renderer, &block);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderDrawRect(renderer, &block);
        }
    }

    for (int ix = 0; ix < 4; ix++)
    {
        for (int iy = 0; iy < 4; iy++)
        {
            if (this->current_block.GetShape()[iy][ix] == 0)
            {
                continue;
            }

            SetDrawColor(this->current_block.GetShape()[iy][ix]);
            block.x = (BLOCK_SIZE * ix) + BLOCK_OFFSET_X +
                      this->current_block.position.x * BLOCK_SIZE;
            block.y = (BLOCK_SIZE * iy) + BLOCK_OFFSET_Y +
                      this->current_block.position.y * BLOCK_SIZE;
            SDL_RenderFillRect(renderer, &block);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderDrawRect(renderer, &block);
        }
    }

    Tetromino next_block = this->block_queue.front();

    for (int ix = 0; ix < 4; ix++)
    {
        for (int iy = 0; iy < 4; iy++)
        {
            if (this->block_queue.front().GetShape()[iy][ix] == 0)
            {
                continue;
            }

            SetDrawColor(next_block.GetShape()[iy][ix]);
            block.x = (BLOCK_SIZE * ix) + 600;
            block.y = (BLOCK_SIZE * iy) + 40;
            SDL_RenderFillRect(renderer, &block);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderDrawRect(renderer, &block);
        }
    }
}

void Tetris::NextBlock()
{
    current_block = block_queue.front();
    block_queue.pop();
    block_queue.push(Tetromino::RandomTetromino());

    current_block.position.x = 3;
}

void Tetris::AddBlock(Tetromino tetromino)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetromino.GetShape()[i][j] == 0)
            {
                continue;
            }
            board[tetromino.position.y + i][tetromino.position.x + j] =
                tetromino.GetShape()[i][j];
        }
    }
}

void Tetris::UpdateLevel()
{
    if (lines % 10 == 0)
    {
        level++;
    }
}

void Tetris::UpdateClearedLines()
{
    bool update_needed = false;
    bool cleared_line_indexes[BOARD_HEIGHT] = {false};

    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        if (std::all_of(board[row], board[row] + BOARD_WIDTH,
                        [](Uint8 i) { return i > 0; }))
        {
            for (int col = 0; col < BOARD_WIDTH; col++)
            {
                board[row][col] = 0;
                Tetris::Render(this->game->renderer);
                SDL_RenderPresent(this->game->renderer);
                SDL_Delay(25);
            }
            update_needed = true;
            cleared_line_indexes[row] = true;
        }
    }

    if (!update_needed)
    {
        return;
    }

    int count = 0;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        if (!cleared_line_indexes[i])
        {
            continue;
        }
        count++;
        for (int relative_row = i; relative_row > 0; relative_row--)
        {
            std::copy(board[relative_row - 1],
                      board[relative_row - 1] + BOARD_WIDTH,
                      board[relative_row]);
        }
        memset(board[0], 0, sizeof(board[0]));
    }

    this->lines += count;

    switch (count)
    {
        case 1:
            this->score += 100 * this->level;
        case 2:
            this->score += 200 * this->level;
        case 3:
            this->score += 300 * this->level;
        case 4:
            this->score += 800 * this->level;
        default:
            this->score += 100;
    }
    this->UpdateLevel();
}

Uint8 (*Tetris::GetBoard())[BOARD_WIDTH] { return this->board; }
