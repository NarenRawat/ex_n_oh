#ifndef GAME_H
#define GAME_H

#include "cursor.h"
#include "player.h"
#include "board.h"
#include <stdbool.h>

typedef struct {
    bool is_running;
    Player current_player;
    Cursor cursor;
    Board board;
} Game;

void init_game(Game *game, int board_size);
void run_game(Game *game);
bool check_winner(Game *game);
void render_game(Game *game);
bool check_winner(Game *game);
void cleanup_game(Game *game);

#endif
