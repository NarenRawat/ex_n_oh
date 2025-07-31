#ifndef POINTER_H
#define POINTER_H

#include "direction.h"
#include "vector2d.h"

typedef Vector2D Pointer;

void move_pointer(Pointer *pointer, Direction dir, int board_size);

#endif
