#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "player.h"
#include "utils.h"
#include "console.h"

bool is_cell_occupied(int size, int row, int col, Player game_board[size][size]) {
    return game_board[row][col] != 0;
}

void render_board(int size, Player board[size][size]) {
    printf(ANSI_CUR_POS, 1, 1);
    printf(ANSI_CLEAR);
    int cell_number = 1;

    int rows = 0;
    int cols = 0;

    get_console_size(&rows, &cols);

    int hpad = (cols - (size * 6 - 1)) / 2;
    int vpad = (rows - (size * 3 - 1)) / 2;

    printf(ANSI_CUR_POS, vpad, 1);
    for (int r = 0; r < size; r++) {
        printf(ANSI_HOR_ABS, hpad);
        for (int c = 0; c < size; c++) {
            switch (board[r][c]) {
                case PLAYER_NONE:
                    printf("  %d  ", cell_number);
                    break;
                case PLAYER_X:
                    printf(ANSI_FG_RED);
                    printf("    ");
                    printf(ANSI_RESET);
                    break;
                case PLAYER_O:
                    printf(ANSI_FG_GREEN);
                    printf("    ");
                    printf(ANSI_RESET);
                    break;
            }

            if (c != size - 1) {
                printf("│");
            }

            cell_number++;
        }

        if (r != size - 1) {
            printf("\n");
            printf("\e[%dG", hpad);
            print_repeat(size, "─────┼");
            printf("\b ");
        }
        printf("\n");
    }
}
