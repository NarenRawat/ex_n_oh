#ifndef BOARD_H
#define BOARD_H

#include "player.h"

bool is_cell_occupied(int size, int row, int col, Player game_board[size][size]);
void render_board(int size, Player board[size][size]);

#endif
