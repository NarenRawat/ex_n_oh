#include <stdio.h>
#include <windows.h>

#include "utils.h"

#define BOARD_SIZE 3

int game_board[BOARD_SIZE][BOARD_SIZE] = {0};

void render_board(int board[BOARD_SIZE][BOARD_SIZE], int size);

void init_console() {
    SetConsoleOutputCP(CP_UTF8);
}

int main(void) {
    init_console();

    render_board(game_board, BOARD_SIZE);

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
