#ifndef CONSOLE_H
#define CONSOLE_H

#include "vector2d.h"

void init_console(void);
int get_input_code(void);
void get_console_size(Vector2D *p_vec);
void cleanup_console(void);

#endif
