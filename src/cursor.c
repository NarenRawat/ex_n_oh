#include "cursor.h"
#include "direction.h"

static void move_cursor_up(Cursor *cursor, int board_size);
static void move_cursor_down(Cursor *cursor, int board_size);
static void move_cursor_left(Cursor *cursor, int board_size);
static void move_cursor_right(Cursor *cursor, int board_size);

void move_cursor(Cursor *cursor, Direction dir, int board_size) {
    switch (dir) {
        case DIR_UP:
            move_cursor_up(cursor, board_size);
            break;
        case DIR_DOWN:
            move_cursor_down(cursor, board_size);
            break;
        case DIR_LEFT:
            move_cursor_left(cursor, board_size);
            break;
        case DIR_RIGHT:
            move_cursor_right(cursor, board_size);
            break;
        default:
            break;
    }
}

static void move_cursor_up(Cursor *cursor, int board_size) {
    (cursor->y)--;
    if (cursor->y < 0) {
        cursor->y = board_size - 1;
    }
}

static void move_cursor_down(Cursor *cursor, int board_size) {
    (cursor->y)++;
    if (cursor->y >= board_size) {
        cursor->y = 0;
    }
}

static void move_cursor_left(Cursor *cursor, int board_size) {
    (cursor->x)--;
    if (cursor->x < 0) {
        cursor->x = board_size - 1;
    }
}

static void move_cursor_right(Cursor *cursor, int board_size) {
    (cursor->x)++;
    if (cursor->x >= board_size) {
        cursor->x = 0;
    }
}

