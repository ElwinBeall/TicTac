#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "tictac.h"

int main(void)
{
    bool quit_playing, game_over = false;

    GameState tictac = init_game();

    while (!quit_playing)
    {
        /* Machine Move */
        make_computer_move(&tictac);

        /* Print or Update Game Board */
        print_game_board(tictac.board);

        /* Check for Win */
        if (game_over = check_win(tictac.winning_lines, tictac.board, &tictac.winner, &tictac.is_game_over))
        {
            printf("\nGame over. ", game_over);
            if (tictac.winner == 1)
                printf("It's a draw.\n");
            else
                printf("Player %c won.\n", tictac.winner == X_VAL ? X_VAL : O_VAL);
            break;
        }

        /* Human Move */
        while (!get_human_move(*tictac.board))
            print_game_board(tictac.board);

        /* Print or Update Game Board */
        print_game_board(tictac.board);

        /* Check for Win */
        if (game_over = check_win(tictac.winning_lines, tictac.board, &tictac.winner, &tictac.is_game_over))
        {
            printf("\nGame over. ", game_over);
            if (tictac.winner == 1)
                printf("It's a draw.\n");
            else
                printf("Player %c won.\n", tictac.winner == X_VAL ? X_VAL : O_VAL);
            break;
        }
    }
    printf("\n");
    for (uint8_t i = 0; i < 5; i++)
        printf("%d, ", tictac.move_queue[i]);
    printf("\n");
    return EXIT_SUCCESS;
}
