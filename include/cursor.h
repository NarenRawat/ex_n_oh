#ifndef CURSOR_H
#define CURSOR_H

#include "direction.h"
#include "vector2d.h"

typedef Vector2D Cursor;

void move_cursor(Cursor *cursor, Direction dir, int board_size);

#endif
