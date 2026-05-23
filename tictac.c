#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define x 'X'   // X or cross
#define o 'O'   // O or naught
#define spc ' ' // empty space

// Since game_board is on the stack, just use array notation
void init_game_board(char game_board[][3])
{
    for (size_t row = 0; row < 3; row++)
    {
        for (size_t col = 0; col < 3; col++)
        {
            game_board[row][col] = spc;
        }
    }
}

// Again, using the stack so no need for pointers
void print_game_board(char game_board[][3])
{
    printf("\n");
    for (size_t row = 0; row < 3; row++)
    {
        printf(" %c | %c | %c \n", game_board[row][0], game_board[row][1], game_board[row][2]);
        if (row < 2)
            printf("---|---|---\n");
    }
    printf("\n");
}

void make_human_move(char game_board[][3])
{
    printf("Enter your move (1-9) ");
    // fgets()
}

int main(void)
{
    const uint8_t winning_lines[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}};
    uint8_t move_queue[5] = {0};

    // knowledge_base of move priority
    uint8_t knowledge_base[10] = {2, 6, 8, 4, 7, 3, 1, 9, 5, 2};
    char game_board[3][3] = {0};

    /*  game_state flags:    only bits 1-4 are used, 8 7 6 5 4 3 2 1
        bit     value   meaning
        1       1       0 = Still playing, 1 = Game Over
        2       2       0 = Player vs Computer, 1 = Computer vs Computer
        3       4       0 = A player won, 1 = It's a Draw (Invalid if bit 1 = 0)
        4       8       0 = Player 1 wins, 1 = Player 2 wins (Invalid if bit 1 = 0 or bit 3 = 1)
    */
    uint8_t game_state = 0;

    /*Remove when done*/ printf("\n%c=%d, %c=%d, '%c'=%d\n", x, x, o, o, spc, spc);
    init_game_board(game_board);
    print_game_board(game_board);

    /*
    /// Game Loop ///
    */

    /* Machine Move */

    /* Print or Update Game Board */

    /* Check for Win */

    /* Human Move */

    /* Print or Update Game Board */

    /* Check for Win */

    /*
    /// End Game Loop ///
    */

    return EXIT_SUCCESS;
}
