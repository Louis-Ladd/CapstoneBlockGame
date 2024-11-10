#include "tetris.hpp"
#include "../log.hpp"

Tetris* Tetris::instance_ptr = nullptr;

#define BLOCK_SIZE 27
#define BLOCK_OFFSET_X 150
#define BLOCK_OFFSET_Y 25

Tetris::Tetris()
{
    /*for (int i = 0; i < 3; i++)
    {
        this->block_queue.push(Tetromino::RandomTetromino());
    }*/

    this->block_queue.push(IShape());
    this->block_queue.push(JShape());
    this->block_queue.push(LShape());
    this->block_queue.push(OShape());
    this->block_queue.push(SShape());
    this->block_queue.push(TShape());
    this->block_queue.push(ZShape());

    this->NextBlock();

    memset(board, 0, sizeof(board));

    for (int i = 0; i < 20; i++)
    {
        board[i][0] = (i % 7) + 1;
    }

    this->game = Game::GetInstance();

    if (this->game == nullptr)
    {
        LOG("Tetris couldn't find game insance");
    }
}

void Tetris::SetDrawColor(int block_state, SDL_Renderer* renderer)
{
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

void Tetris::Update()
{
    LOG("Delta Time: %f", this->game->delta_time);
    if (SDL_GetTicks() - this->block_fall_cooldown >= 150 &&
        !this->current_block.CheckIfLanded(this->board))
    {
        this->current_block.MoveDown();
        this->block_fall_cooldown = SDL_GetTicks();
        this->block_drop_grace = 5;
    }

    if (this->current_block.CheckIfLanded(this->board))
    {
        LOG("Block is landed...");
        if (this->block_drop_grace >= 0)
        {
            LOG("Grace timer is more than 0, subtracting delta_time");
            this->block_drop_grace -= this->game->delta_time;
        }
        else
        {
            LOG("Grace timer is less than 0, resetting and next block");
            this->AddBlock(this->current_block);
            this->NextBlock();
            this->UpdateClearedLines();
            this->block_drop_grace = 5;
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

    if (this->game->event_handler.ResetKey(SDLK_SPACE))
    {
        this->current_block.RotateClockwise(board);
    }
}

void Tetris::Render(SDL_Renderer* renderer)
{
    SDL_Rect block = {0, 0, BLOCK_SIZE, BLOCK_SIZE};

    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        for (int y = 0; y < BOARD_HEIGHT; y++)
        {
            SetDrawColor(this->board[y][x], renderer);

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

            SetDrawColor(this->current_block.GetShape()[iy][ix], renderer);
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

            SetDrawColor(next_block.GetShape()[iy][ix], renderer);
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

void Tetris::UpdateClearedLines()
{
    bool update_needed = false;
    std::vector<int> cleared_line_indexes;

    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        if (std::all_of(board[row], board[row] + BOARD_WIDTH,
                        [](int i) { return i > 0; }))
        {
            for (int col = 0; col < BOARD_WIDTH; col++)
            {
                board[row][col] = 0;
                Tetris::Render(this->game->renderer);
                SDL_RenderPresent(this->game->renderer);
                std::this_thread::sleep_for(std::chrono::milliseconds(25));
            }
            update_needed = true;
            cleared_line_indexes.push_back(row);
        }
    }

    if (!update_needed)
    {
        return;
    }

    for (int index : cleared_line_indexes)
    {
        for (int relative_row = index; relative_row > 0; relative_row--)
        {
            std::copy(board[relative_row - 1],
                      board[relative_row - 1] + BOARD_WIDTH,
                      board[relative_row]);
        }
        memset(board[0], 0, sizeof(board[0]));
    }
}

int (*Tetris::GetBoard())[BOARD_WIDTH] { return this->board; }
