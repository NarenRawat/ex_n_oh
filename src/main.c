#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "utils.h"
#include "console.h"
#include "player.h"
#include "board.h"

#define BOARD_SIZE 3

Player game_board[BOARD_SIZE][BOARD_SIZE] = {0};

int main(void) {
    init_console();

    printf(ANSI_CLEAR);

    Player current_player = PLAYER_X;
    int user_move;
    int user_move_col;
    int user_move_row;
    int total_cell_occupied = 0;

    while (1) {
        render_board(BOARD_SIZE, game_board);
        do {
            user_move = get_user_move(BOARD_SIZE);
            user_move_col = (user_move - 1) % BOARD_SIZE;
            user_move_row = (user_move - 1) / BOARD_SIZE;
        } while (is_cell_occupied(BOARD_SIZE, user_move_row, user_move_col, game_board));

        game_board[user_move_row][user_move_col] = current_player;

        total_cell_occupied++;

        if (check_winner(BOARD_SIZE, game_board, current_player)) {
            render_board(BOARD_SIZE, game_board);
            printf("%c won!\n", current_player == PLAYER_X ? 'X' : 'O');
            break;
        } else if (total_cell_occupied == 9) { // all cells are filled
            render_board(BOARD_SIZE, game_board);
            printf("It's a draw!\n");
            break;
        }

        current_player = current_player == PLAYER_X ? PLAYER_O : PLAYER_X;
    }

    return 0;
}
