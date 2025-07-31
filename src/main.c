#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "utils.h"
#include "console.h"
#include "player.h"
#include "board.h"
#include "pointer.h"
#include "game.h"
#include "direction.h"

#define BOARD_SIZE 3

Game game;

void cleanup(void);

int main(void) {
    atexit(cleanup);

    init_console();
    init_game(&game, BOARD_SIZE);

    int input_code;
    int total_cell_occupied = 0;

    while (1) {
        render_game(&game);

        input_code = get_input_code();

        switch(input_code) {
            case VK_ESCAPE:
            case 'Q':
                return 0;
                break;
            case VK_UP:
            case 'W':
            case 'K':
                move_pointer(&game.pointer, DIR_UP, BOARD_SIZE);
                break;
            case VK_DOWN:
            case 'S':
            case 'J':
                move_pointer(&game.pointer, DIR_DOWN, BOARD_SIZE);
                break;
            case VK_LEFT:
            case 'A':
            case 'H':
                move_pointer(&game.pointer, DIR_LEFT, BOARD_SIZE);
                break;
            case VK_RIGHT:
            case 'D':
            case 'L':
                move_pointer(&game.pointer, DIR_RIGHT, BOARD_SIZE);
                break;
            case VK_RETURN:
                game.board.data[game.pointer.y][game.pointer.x] = game.current_player;
                total_cell_occupied++;

                    if (check_winner(&game)) {
                        render_game(&game);
                        printf("%c won!\n", game.current_player == PLAYER_X ? 'X' : 'O');
                        break;
                    } else if (total_cell_occupied == BOARD_SIZE * BOARD_SIZE) { // all cells are filled
                        render_game(&game);
                        printf("It's a draw!\n");
                        break;
                    }
                game.current_player = game.current_player == PLAYER_X ? PLAYER_O : PLAYER_X;
                break;
        }

    }

    return 0;
}

void cleanup(void) {
    cleanup_console();
    cleanup_game(&game);
}
