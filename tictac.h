#pragma once

#define ROWS 3
#define COLS 3
// define players and empty space
#define X_VAL 'X'
#define O_VAL 'O'
#define SPC ' '
// convert 1D array indexing to 2D matrix indexing and vice versa
#define GET_INDEX(row, num_cols, col) ((row) * (num_cols) + (col))
#define GET_ROW(index, num_cols) ((index) / (num_cols))
#define GET_COL(index, num_cols) ((index) % (num_cols))

typedef struct GameState
{
    const uint8_t winning_lines[8][COLS];
    uint8_t knowledge_base[10];
    uint8_t board[ROWS][COLS];
    uint8_t move_queue[5];
    uint8_t move_count;
    uint8_t winner; // X_VAL, O_VAL, 1 for Draw
    bool is_game_over;
} GameState;

typedef struct RowCol
{
    uint8_t row;
    uint8_t col;
} RowCol;

// Initialize game
GameState init_game(void)
{
    GameState game = {
        .winning_lines = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},
            {0, 4, 8},
            {2, 4, 6}},
        .knowledge_base = {1, 5, 7, 3, 6, 2, 0, 8, 4, 1},
        .board = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        .move_queue = {0, 0, 0, 0, 0},
        .move_count = 0,
        .winner = 0,
        .is_game_over = false};
    return game;
}

// Reset game
void reset_game(struct GameState *game)
{
    for (uint8_t row = 0; row < 3; row++)
    {
        for (uint8_t col = 0; col < 3; col++)
        {
            game->board[row][col] = ' ';
        }
    }

    for (uint8_t cell = 0; cell < 5; cell++)
    {
        game->move_queue[cell] = 0;
    }

    game->move_count = 0;
    game->winner = 0;
    game->is_game_over = false;
}

bool cell_available(uint8_t board[][COLS])
{
    for (uint8_t row = 0; row < 3; row++)
    {
        if (board[row][0] == ' ' ||
            board[row][1] == ' ' ||
            board[row][2] == ' ')
            return true;
    }
    return false;
}

// Print game board
void print_game_board(uint8_t board[][COLS])
{
    uint8_t board_map[][COLS] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    printf("\n");
    for (uint8_t row = 0; row < 3; row++)
    {
        printf(" %c | %c | %c \t %c | %c | %c \n",
               board[row][0], board[row][1], board[row][2],
               board_map[row][0], board_map[row][1], board_map[row][2]);
        if (row < 2)
            printf("---|---|---\t---|---|---\n");
    }
    printf("\n");
}

/* Human Move */
bool get_human_move(uint8_t *board)
{
    uint8_t discard, input = 0;

    printf("Enter your move (1-9) ");
    input = getchar();
    while ((discard = getchar() != '\n' && discard != EOF))
        ;

    if (input < '1' || input > '9')
        return false;
    else if (board[input - 49] != SPC)
    {
        printf("%s occupied location %c.\n",
               board[input - 49] == O_VAL ? "You have already" : "Player X has already",
               input);
        return false;
    }
    else
    {
        board[input - 49] = O_VAL; // subtract ascii value of '1'
        return true;
    }
}

/* Computer Move */
bool make_computer_move(struct GameState *game)
{
    // Winning/Blocking move
    for (uint8_t row = 0; row < 8; row++)
    {
        uint8_t A_x, A_y, B_x, B_y, C_x, C_y; // 2D row/col
        A_x = GET_ROW(game->winning_lines[row][0], COLS);
        A_y = GET_COL(game->winning_lines[row][0], COLS);

        B_x = GET_ROW(game->winning_lines[row][1], COLS);
        B_y = GET_COL(game->winning_lines[row][1], COLS);

        C_x = GET_ROW(game->winning_lines[row][2], COLS);
        C_y = GET_COL(game->winning_lines[row][2], COLS);

        if (game->board[A_x][A_y] ==
                game->board[B_x][B_y] &&
            game->board[C_x][C_y] == SPC &&
            game->board[A_x][A_y] != SPC)
        {
            game->board[C_x][C_y] = X_VAL;
            game->move_queue[game->move_count] = GET_INDEX(C_x, COLS, C_y);
            game->move_count++;
            // remove printf()
            printf("WB-C row=%d, col=%d\n", C_x, C_y);
            printf("WB ind=%d", game->move_queue[game->move_count - 1]);
            if (cell_available(game->board))
                return game->is_game_over;
            else
            {
                printf("Draw\n");
                game->winner = 1;
                return game->is_game_over = true;
            }
        }
        else if (
            game->board[A_x][A_y] ==
                game->board[C_x][C_y] &&
            game->board[B_x][B_y] == SPC &&
            game->board[A_x][A_y] != SPC)
        {
            game->board[B_x][B_y] = X_VAL;
            game->move_queue[game->move_count] = GET_INDEX(B_x, COLS, B_y);
            game->move_count++;
            // remove printf()
            printf("WB-B row=%d, col=%d\n", B_x, B_y);
            printf("WB ind=%d", game->move_queue[game->move_count - 1]);
            if (cell_available(game->board))
                return game->is_game_over;
            else
            {
                printf("Draw\n");
                game->winner = 1;
                return game->is_game_over = true;
            }
        }
        else if (
            game->board[B_x][B_y] ==
                game->board[C_x][C_y] &&
            game->board[A_x][A_y] == SPC &&
            game->board[B_x][B_y] != SPC)
        {
            game->board[A_x][A_y] = X_VAL;
            game->move_queue[game->move_count] = GET_INDEX(A_x, COLS, A_y);
            game->move_count++;
            // remove printf()
            printf("WB-A row=%d, col=%d\n", A_x, A_y);
            printf("WB ind=%d", game->move_queue[game->move_count - 1]);
            if (cell_available(game->board))
                return game->is_game_over;
            else
            {
                printf("Draw\n");
                game->winner = 1;
                return game->is_game_over = true;
            }
        }
    }

    // Knowledge Base move
    for (uint8_t cell = 0; cell < 10; cell++)
    {
        uint8_t row = GET_ROW(game->knowledge_base[cell], COLS);
        uint8_t col = GET_COL(game->knowledge_base[cell], COLS);

        if (game->board[row][col] == SPC)
        {
            game->board[row][col] = X_VAL;
            game->move_queue[game->move_count] = GET_INDEX(row, COLS, col);
            game->move_count++;
            // remove printf()
            printf("KB ind=%d", game->move_queue[game->move_count - 1]);

            if (cell_available(game->board))
                return game->is_game_over;
            else
            {
                game->winner = 1;
                return game->is_game_over = true;
            }
        }
    }

    // Random move?

    // Fail to a draw
    game->winner = 1;
    return game->is_game_over = true;
}

/* Check for Win */
bool check_win(const uint8_t winning_lines[][COLS], uint8_t board[][COLS], uint8_t *winner, bool *is_game_over)
{
    for (uint8_t row = 0; row < 8; row++)
    {
        uint8_t A_x, A_y, B_x, B_y, C_x, C_y; // 2D row/col
        A_x = GET_ROW(winning_lines[row][0], COLS);
        A_y = GET_COL(winning_lines[row][0], COLS);

        B_x = GET_ROW(winning_lines[row][1], COLS);
        B_y = GET_COL(winning_lines[row][1], COLS);

        C_x = GET_ROW(winning_lines[row][2], COLS);
        C_y = GET_COL(winning_lines[row][2], COLS);

        if (board[A_x][A_y] == SPC)
        {
            continue;
        }

        if (board[A_x][A_y] ==
                board[B_x][B_y] &&
            board[A_x][A_y] ==
                board[C_x][C_y])
        {
            *winner = (board[A_x][A_y] == X_VAL) ? X_VAL : O_VAL;
            return *is_game_over = true;
        }
    }
    if (!cell_available(board))
    {
        *winner = 1;
        return *is_game_over = true;
    }
    return *is_game_over = false;
}
