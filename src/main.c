#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "utils.h"

#define BOARD_SIZE 3

int game_board[BOARD_SIZE][BOARD_SIZE] = {0};

void render_board(int board[BOARD_SIZE][BOARD_SIZE], int size);

void init_console() {
    SetConsoleOutputCP(CP_UTF8);
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

int main(void) {
    init_console();

    bool is_x_turn = true;
    int user_move;
    int user_move_col;
    int user_move_row;

    while (1) {
        render_board(game_board, BOARD_SIZE);
        do {
            user_move = get_user_move();
            user_move_col = (user_move - 1) % BOARD_SIZE;
            user_move_row = (user_move - 1) / BOARD_SIZE;
        } while (is_cell_occupied(user_move_row, user_move_col));

        if (is_x_turn) {
            game_board[user_move_row][user_move_col] = 1;
        } else {
            game_board[user_move_row][user_move_col] = 2;
        }

        is_x_turn = !is_x_turn;
    }

    return 0;
}

void render_board(int board[BOARD_SIZE][BOARD_SIZE], int size) {
    int cell_number = 1;

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            switch (board[r][c]) {
                case 0:
                    printf("  %d  ", cell_number);
                    break;
                case 1:
                    printf("    ");
                    break;
                case 2:
                    printf("    ");
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
