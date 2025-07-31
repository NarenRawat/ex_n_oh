#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "utils.h"
#include "console.h"

#define BOARD_SIZE 3
#define ANSI_FG_RED "\e[38;2;255;0;0m"
#define ANSI_FG_GREEN "\e[38;2;0;255;0m"
#define ANSI_RESET "\e[0m"
#define ANSI_CLEAR "\e[2J"
#define ANSI_CUR_POS "\e[%d;%dH"

typedef enum {
    PLAYER_NONE = 0,
    PLAYER_X,
    PLAYER_O
} Player;

Player game_board[BOARD_SIZE][BOARD_SIZE] = {0};

void render_board(Player board[BOARD_SIZE][BOARD_SIZE], int size);
bool is_cell_occupied(int row, int col);
int get_user_move();
bool check_winner(Player current_player);

int main(void) {
    init_console();
    return 0;
    printf(ANSI_CLEAR);

    Player current_player = PLAYER_X;
    int user_move;
    int user_move_col;
    int user_move_row;
    int total_cell_occupied = 0;

    while (1) {
        render_board(game_board, BOARD_SIZE);
        do {
            user_move = get_user_move();
            user_move_col = (user_move - 1) % BOARD_SIZE;
            user_move_row = (user_move - 1) / BOARD_SIZE;
        } while (is_cell_occupied(user_move_row, user_move_col));

        game_board[user_move_row][user_move_col] = current_player;

        total_cell_occupied++;

        if (check_winner(current_player)) {
            render_board(game_board, BOARD_SIZE);
            printf("%c won!\n", current_player == PLAYER_X ? 'X' : 'O');
            break;
        } else if (total_cell_occupied == 9) { // all cells are filled
            render_board(game_board, BOARD_SIZE);
            printf("It's a draw!\n");
            break;
        }

        current_player = current_player == PLAYER_X ? PLAYER_O : PLAYER_X;
    }

    return 0;
}


bool check_winner(Player current_player) {
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

    for (int i = 0; i < BOARD_SIZE; i++) {
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

bool is_cell_occupied(int row, int col) {
    return game_board[row][col] != 0;
}

int get_user_move() {
    int min_index = 1;
    int max_index = BOARD_SIZE * BOARD_SIZE;

    int res;
    do {
        printf("Enter cell number(%d-%d): ", min_index, max_index);
        scanf("%d", &res);
    } while (res < min_index || res > max_index);

    return res;
}

void render_board(Player board[BOARD_SIZE][BOARD_SIZE], int size) {
    printf(ANSI_CUR_POS, 1, 1);
    printf(ANSI_CLEAR);
    int cell_number = 1;

    for (int r = 0; r < size; r++) {
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
            print_repeat(size, "─────┼");
            printf("\b ");
        }
        printf("\n");
    }
}
