#include <stdio.h>

#include "player.h"

bool check_winner(int size, Player game_board[size][size], Player current_player) {
    bool diagonal_equal = game_board[0][0] == current_player
                       && game_board[1][1] == current_player
                       && game_board[2][2] == current_player;
    if (diagonal_equal) {
        return true;
    }

    bool sec_diag_equal = game_board[0][2] == current_player
                       && game_board[1][1] == current_player
                       && game_board[2][0] == current_player;

    if (sec_diag_equal) {
        return true;
    }

    for (int i = 0; i < size; i++) {
        bool col_equal = game_board[0][i] == current_player
                      && game_board[1][i] == current_player
                      && game_board[2][i] == current_player;

        if (col_equal) {
            return true;
        }

        bool row_equal = game_board[i][0] == current_player
                      && game_board[i][1] == current_player
                      && game_board[i][2] == current_player;

        if (row_equal) {
            return true;
        }
    }

    return false;
}

int get_user_move(int size) {
    int min_index = 1;
    int max_index = size * size;

    int res;
    do {
        printf("Enter cell number(%d-%d): ", min_index, max_index);
        scanf("%d", &res);
    } while (res < min_index || res > max_index);

    return res;
}

