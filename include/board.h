#ifndef BOARD_H
#define BOARD_H

#include "player.h"
#include "vector2d.h"
#include "pointer.h"

typedef struct {
    Player **data;
    int size;
} Board;

void init_board(Board *board, int board_size);
bool is_cell_occupied(Board *board, Vector2D cell);
void render_board(Board *board, Player current_player, Pointer pointer);
void cleanup_board(Board *board);

#endif
