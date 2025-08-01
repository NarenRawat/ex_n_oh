#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "board.h"
#include "player.h"
#include "utils.h"
#include "console.h"
#include "vector2d.h"
#include "cursor.h"

void init_board(Board *board, int board_size) {
    board->size = board_size;

    board->data = malloc(board->size * sizeof(Player *));
    for (int i = 0; i < board->size; i++) {
        board->data[i] = malloc(board->size * sizeof(Player));
        memset(board->data[i], PLAYER_NONE, board->size * sizeof(Player));
    }
}

bool is_cell_occupied(Board *board, Vector2D cell) {
    return board->data[cell.y][cell.x] != PLAYER_NONE;
}

void render_board(Board *board, Player current_player, Cursor cursor) {
    Vector2D console_size;
    get_console_size(&console_size);

    int size = board->size;

    int hpad = (console_size.x - (board->size * 6 - 1)) / 2;
    int vpad = (console_size.y - (board->size * 3 - 1)) / 2;

    printf(ANSI_CUR_POS, vpad, 1);

    for (int r = 0; r < size; r++) {
        printf(ANSI_HOR_ABS, hpad);
        for (int c = 0; c < size; c++) {
            switch (board->data[r][c]) {
                case PLAYER_NONE:
                    if (cursor.y == r && cursor.x == c) {
                        // printf(" \e[7m   \e[0m ");
                        switch (current_player) {
                            case PLAYER_X:
                                printf("    ");
                                break;
                            case PLAYER_O:
                                printf("    ");
                                break;
                            case PLAYER_NONE:
                            default:
                            break;
                        }
                    } else {
                        printf("     ");
                    }
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

void cleanup_board(Board *board) {
    int size = board->size;
    for (int i = 0; i < size; i++) {
        free(board->data[i]);
    }
    free(board->data);
}
