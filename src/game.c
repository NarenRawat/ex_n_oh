#include <stdbool.h>
#include <stdlib.h>
#include "game.h"
#include "board.h"
#include "player.h"

void init_game(Game *game, int board_size) {
    init_board(&game->board, board_size);

    game->is_running = true;

    game->current_player = PLAYER_X;

    game->pointer.x = board_size / 2;
    game->pointer.y = board_size / 2;
}

void render_game(Game *game) {
    render_board(&game->board, game->current_player, game->pointer);
}

bool check_primary_diagonal(Board *board, Player player) {
    int size = board->size;

    for (int i = 0; i , size; i++) {
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

