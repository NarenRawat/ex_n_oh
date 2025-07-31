#include "pointer.h"
#include "direction.h"

static void move_pointer_up(Pointer *pointer, int board_size);
static void move_pointer_down(Pointer *pointer, int board_size);
static void move_pointer_left(Pointer *pointer, int board_size);
static void move_pointer_right(Pointer *pointer, int board_size);

void move_pointer(Pointer *pointer, Direction dir, int board_size) {
    switch (dir) {
        case DIR_UP:
            move_pointer_up(pointer, board_size);
            break;
        case DIR_DOWN:
            move_pointer_down(pointer, board_size);
            break;
        case DIR_LEFT:
            move_pointer_left(pointer, board_size);
            break;
        case DIR_RIGHT:
            move_pointer_right(pointer, board_size);
            break;
        default:
            break;
    }
}

static void move_pointer_up(Pointer *pointer, int board_size) {
    (pointer->y)--;
    if (pointer->y < 0) {
        pointer->y = board_size - 1;
    }
}

static void move_pointer_down(Pointer *pointer, int board_size) {
    (pointer->y)++;
    if (pointer->y >= board_size) {
        pointer->y = 0;
    }
}

static void move_pointer_left(Pointer *pointer, int board_size) {
    (pointer->x)--;
    if (pointer->x < 0) {
        pointer->x = board_size - 1;
    }
}

static void move_pointer_right(Pointer *pointer, int board_size) {
    (pointer->x)++;
    if (pointer->x >= board_size) {
        pointer->x = 0;
    }
}

