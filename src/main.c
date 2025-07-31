#include <stdlib.h>

#include "console.h"
#include "game.h"

#define BOARD_SIZE 3

Game game;

void cleanup(void);

int main(void) {
    atexit(cleanup);

    init_console();
    init_game(&game, BOARD_SIZE);
    run_game(&game);

    return 0;
}

void cleanup(void) {
    cleanup_console();
    cleanup_game(&game);
}
