#include "tetris.hpp"
#include "../log.hpp"
#include <string>

Tetris* Tetris::instance_ptr = nullptr;

#define BLOCK_SIZE 27
#define BLOCK_OFFSET_X 150
#define BLOCK_OFFSET_Y 25

void Tetris::BuildUI()
{
    this->game->event_handler.SetMouseCallback([this](SDL_Point point)
                                               { HandleMouseClick(point); });

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color dark_cyan = {0, 171, 196, 255};

    // Game UI elements
    UILabel* level_label =
        new UILabel(450, 180, this->ui_manager.GetDefaultFont(3),
                    "Level: Not Set", white, this->game->renderer);

    UILabel* score_label =
        new UILabel(450, 225, this->ui_manager.GetDefaultFont(3),
                    "Score: Not Set", white, this->game->renderer);

    UILabeledButton* play_button = new UILabeledButton(
        500, 350, 100, 100, white, dark_cyan,
        this->ui_manager.GetDefaultFont(2), this->game->renderer, "Next");
    play_button->button->SetOnClickFunction(
        [this](void)
        {
            this->level++;
            this->UpdateLevel();
        });
    this->ui_manager.AddUIElement("Next", play_button);
    this->ui_manager.AddUIElement("Level", level_label);
    this->ui_manager.AddUIElement("Score", score_label);

    // Game over UI elements
    UILabel* game_over_label =
        new UILabel(0, 0, this->ui_manager.GetDefaultFont(3), "Game Over",
                    white, this->game->renderer);
    game_over_label->SetPosition(
        {(SCREEN_WIDTH / 2) - (game_over_label->GetTextWidth() / 2), 50});
    game_over_label->SetEnabled(false);

    this->ui_manager.AddUIElement("GameOverLabel", game_over_label);
}

// This is our callback function that we give the event handler
// This function is called whenever the mouse is clicked.
void Tetris::HandleMouseClick(SDL_Point point)
{
    this->ui_manager.InvokeClickEvents(point);
}

// Sets up Tetris board and tees up the blocks to be dropped.
Tetris::Tetris() : game(Game::GetInstance()), ui_manager(this->game->renderer)
{
    this->BuildUI();

    this->UpdateLevel();
    this->UpdateScore();

    for (int i = 0; i < 3; i++)
    {
        this->block_queue.push(Tetromino::RandomTetromino());
    }

    this->NextBlock();

    memset(board, 0, sizeof(board));

    if (this->game == nullptr)
    {
        LOG("Tetris couldn't find game insance");
    }

    this->game_state = GameState::Running;
}

Tetris::~Tetris() { this->game = nullptr; }

// Set the SDL draw color, this is inlined as we call it a lot in loops
// So we don't want to jump to it constantly just for one function call.
inline void Tetris::SetDrawColor(int block_state, Uint8 tint)
{
    SDL_Renderer* renderer = this->game->renderer;
    switch (block_state)
    {
        case 0:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Black
            break;
        case 1:
            SDL_SetRenderDrawColor(renderer, 0, 255 - tint, 240 - tint,
                                   0); // Cyan
            break;
        case 2:
            SDL_SetRenderDrawColor(renderer, 175 - tint, 0, 239 - tint,
                                   0); // Purple
            break;
        case 3:
            SDL_SetRenderDrawColor(renderer, 255 - tint, 188 - tint, 0,
                                   0); // Orange
            break;
        case 4:
            SDL_SetRenderDrawColor(renderer, 0, 111 - tint, 255 - tint,
                                   0); // Blue
            break;
        case 5:
            SDL_SetRenderDrawColor(renderer, 0, 245 - tint, 41 - tint,
                                   0); // Green
            break;
        case 6:
            SDL_SetRenderDrawColor(renderer, 238 - tint, 0, 24, 0); // Red
            break;
        case 7:
            SDL_SetRenderDrawColor(renderer, 246 - tint, 246 - tint, 0,
                                   0); // Yellow
            break;
        default:
            SDL_GetRenderDrawColor(renderer, 0, 0, 0, 0);
            break;
    }
}

void Tetris::ResetGraceTimer() { this->block_drop_grace = 0.3; }

void Tetris::DropCurrentBlock()
{
    this->AddBlock(this->current_block);
    this->NextBlock();
    this->UpdateClearedLines();
    ResetGraceTimer();
}

// This is called every frame, this is meant to handle only logic.
void Tetris::Update()
{

    if (this->game_state == GameState::Lost)
    {
        return;
    }

    if (SDL_GetTicks() - this->block_fall_cooldown >=
            600 / (1 + 0.3f * (this->level + 2)) &&
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
    if (this->game->event_handler.IsKeyDown(SDLK_s) &&
        !this->current_block.CheckIfLanded(board) &&
        SDL_GetTicks() - this->block_fall_cooldown >= 50)
    {
        this->current_block.position.y++;
        this->block_fall_cooldown = SDL_GetTicks();
    }
    if (this->game->event_handler.ResetKey(SDLK_p))
    {
        this->level++;
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

// This is called every frame, this is only meant to handle drawing and
// rendering.
void Tetris::Render(SDL_Renderer* renderer)
{
    if (this->game_state == GameState::Lost)
    {
        this->ui_manager.Render();
        return;
    }
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

    // Draw the current board state.

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

    // Draw the current block (falling block)

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

    // Draws the next block preview.

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

    // Render UI after we have drawn our game elements.
    this->ui_manager.Render();
}

void Tetris::NextBlock()
{
    current_block = block_queue.front();
    block_queue.pop();
    block_queue.push(Tetromino::RandomTetromino());

    current_block.position.x = 3;
}

// Updates the board state with a given tetromino
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

// Checks what level we should be right now and then update the level label
void Tetris::UpdateLevel()
{
    if (this->lines % 10 == 0 && this->lines != 0)
    {
        this->level++;
    }
    UILabel* level_label =
        dynamic_cast<UILabel*>(this->ui_manager.GetUIElement("Level"));
    level_label->SetText(this->game->renderer,
                         "Level: " + std::to_string(this->level));
}

// Update the score label.
void Tetris::UpdateScore()
{
    UILabel* score_label =
        dynamic_cast<UILabel*>(this->ui_manager.GetUIElement("Score"));
    score_label->SetText(this->game->renderer,
                         "Score: " + std::to_string(this->score));
}

// Check the board for lines, game over if topped out.
// Updates score according to how many lines were cleared.
void Tetris::UpdateClearedLines()
{
    // Check if any block occupies the top of the board.
    // Game over if so.
    if (std::accumulate(std::begin(this->board[0]), std::end(this->board[0]), 0,
                        std::plus<int>()) > 0)
    {
        this->game_state = GameState::Lost;
        ResetBoard();
        this->SetGameUIElements(false);
        this->SetGameOverUIElements(true);
        return;
    }
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
            break;
        case 2:
            this->score += 200 * this->level;
            break;
        case 3:
            this->score += 300 * this->level;
            break;
        case 4:
            this->score += 800 * this->level;
            break;
        default:
            this->score += 100;
    }
    this->UpdateLevel();
    this->UpdateScore();
}

void Tetris::SetGameUIElements(bool enabled)
{
    this->ui_manager.GetUIElement("Next")->SetEnabled(enabled);
    this->ui_manager.GetUIElement("Level")->SetEnabled(enabled);
    this->ui_manager.GetUIElement("Score")->SetEnabled(enabled);
}

void Tetris::SetGameOverUIElements(bool enabled)
{
    this->ui_manager.GetUIElement("GameOverLabel")->SetEnabled(enabled);
}

void Tetris::ResetBoard() { memset(board, 0, sizeof(this->board)); }

Uint8 (*Tetris::GetBoard())[BOARD_WIDTH] { return this->board; }
