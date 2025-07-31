#ifndef PLAYER_H
#define PLAYER_H

typedef enum {
    PLAYER_NONE = 0,
    PLAYER_X,
    PLAYER_O
} Player;


bool check_winner(int size, Player game_board[size][size], Player current_player);
int get_user_move(int size);

#endif
