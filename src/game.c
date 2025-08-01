#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

#include "game.h"
#include "board.h"
#include "player.h"
#include "console.h"
#include "direction.h"

void init_game(Game *game, int board_size) {
    init_board(&game->board, board_size);

    game->is_running = true;

    game->current_player = PLAYER_X;

    game->cursor.x = board_size / 2;
    game->cursor.y = board_size / 2;
}

void run_game(Game *game) {
    int input_code = get_input_code();
    int total_cell_occupied = 0;

    while (game->is_running) {
        render_game(game);

        input_code = get_input_code();

        switch (input_code) {
            case VK_ESCAPE:
            case 'Q':
                return;
                break;
            case VK_UP:
            case 'W':
            case 'K':
                move_cursor(&game->cursor, DIR_UP, game->board.size);
                break;
            case VK_DOWN:
            case 'S':
            case 'J':
                move_cursor(&game->cursor, DIR_DOWN, game->board.size);
                break;
            case VK_LEFT:
            case 'A':
            case 'H':
                move_cursor(&game->cursor, DIR_LEFT, game->board.size);
                break;
            case VK_RIGHT:
            case 'D':
            case 'L':
                move_cursor(&game->cursor, DIR_RIGHT, game->board.size);
                break;

            case VK_RETURN:
                if (!is_cell_occupied(&game->board, game->cursor)) {
                    game->board.data[game->cursor.y][game->cursor.x] = game->current_player;
                    total_cell_occupied++;

                    if (check_winner(game)) {
                        render_game(game);
                        printf("%c won!\n", game->current_player == PLAYER_X ? 'X' : 'O');
                    } else if (total_cell_occupied == game->board.size * game->board.size) { // all cells are filled
                        render_game(game);
                        printf("It's a draw!\n");
                    }

                    game->current_player = game->current_player == PLAYER_X ? PLAYER_O : PLAYER_X;
                }
                break;
            default:
                break;
        }
    }
}

void render_game(Game *game) {
    render_board(&game->board, game->current_player, game->cursor);
}

bool check_primary_diagonal(Board *board, Player player) {
    int size = board->size;

    for (int i = 0; i < size; i++) {
        if (board->data[i][i] != player) {
            return false;
        }
    }

    return true;
}

bool check_sec_diagonal(Board *board, Player player) {
    int size = board->size;

    for (int i = 0; i < size; i++) {
        if (board->data[i][size - i - 1] != player ) {
            return false;
        }
    }
    return true;
}

bool check_col(Board *board, int col, Player player) {
    int size = board->size;

    for (int i = 0; i < size; i++) {
        if (board->data[i][col] != player) {
            return false;
        }
    }

    return true;
}

bool check_row(Board *board, int row, Player player) {
    int size = board->size;

    for (int i = 0; i < size; i++) {
        if (board->data[row][i] != player) {
            return false;
        }
    }

    return true;
}

bool check_winner(Game *game) {
    int size = game->board.size;

    if (check_primary_diagonal(&game->board, game->current_player)) {
        return true;
    }

    if (check_sec_diagonal(&game->board, game->current_player)) {
        return true;
    }

    for (int i = 0; i < size; i++) {
        if (check_col(&game->board, i, game->current_player)) {
            return true;
        }
        if (check_row(&game->board, i, game->current_player)) {
            return true;
        }
    }

    return false;
}

void cleanup_game(Game *game) {
    cleanup_board(&game->board);
}

