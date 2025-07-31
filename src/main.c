#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "utils.h"
#include "console.h"
#include "player.h"
#include "board.h"

#define BOARD_SIZE 3

Player game_board[BOARD_SIZE][BOARD_SIZE] = {0};

void cleanup(void);
void move_pointer(int *pointer_x, int *pointer_y, char dir, int board_size) {
    switch (dir) {
        case 'u':
            (*pointer_y)--;
            if (*pointer_y < 0) {
                *pointer_y = board_size - 1;
            }
            break;
        case 'd':
            (*pointer_y)++;
            if (*pointer_y >= board_size) {
                *pointer_y = 0;
            }
            break;
        case 'l':
            (*pointer_x)--;
            if (*pointer_x < 0) {
                *pointer_x = board_size - 1;
            }
            break;
        case 'r':
            (*pointer_x)++;
            if (*pointer_x >= board_size) {
                *pointer_x = 0;
            }
            break;
    }
}

int main(void) {
    init_console();

    atexit(cleanup);

    int pointer_x = BOARD_SIZE / 2;
    int pointer_y = BOARD_SIZE / 2;

    printf(ANSI_CLEAR);

    Player current_player = PLAYER_X;
    int total_cell_occupied = 0;
    int input_code;

    while (1) {
        render_board(BOARD_SIZE, game_board, pointer_x, pointer_y);

        input_code = get_input_code();

        switch(input_code) {
            case VK_ESCAPE:
            case 'Q':
                return 0;
                break;
            case VK_UP:
            case 'W':
            case 'K':
                move_pointer(&pointer_x, &pointer_y, 'u', BOARD_SIZE);
                break;
            case VK_DOWN:
            case 'S':
            case 'J':
                move_pointer(&pointer_x, &pointer_y, 'd', BOARD_SIZE);
                break;
            case VK_LEFT:
            case 'A':
            case 'H':
                move_pointer(&pointer_x, &pointer_y, 'l', BOARD_SIZE);
                break;
            case VK_RIGHT:
            case 'D':
            case 'L':
                move_pointer(&pointer_x, &pointer_y, 'r', BOARD_SIZE);
                break;
            case VK_RETURN:
                game_board[pointer_y][pointer_x] = current_player;
                total_cell_occupied++;

                    if (check_winner(BOARD_SIZE, game_board, current_player)) {
                        render_board(BOARD_SIZE, game_board, -1, -1);
                        printf("%c won!\n", current_player == PLAYER_X ? 'X' : 'O');
                        break;
                    } else if (total_cell_occupied == 9) { // all cells are filled
                        render_board(BOARD_SIZE, game_board, -1, -1);
                        printf("It's a draw!\n");
                        break;
                    }
                current_player = current_player == PLAYER_X ? PLAYER_O : PLAYER_X;
                break;
        }

    }

    return 0;
}

void cleanup(void) {
    cleanup_console();
}
