#ifndef UTILS_H
#define UTILS_H

#define ANSI_FG_RED "\e[38;2;255;0;0m"
#define ANSI_FG_GREEN "\e[38;2;0;255;0m"
#define ANSI_RESET "\e[0m"
#define ANSI_CLEAR "\e[2J"
#define ANSI_CUR_POS "\e[%d;%dH"
#define ANSI_HOR_ABS "\e[%dG"

void print_repeat(int count, char *format, ...);

#endif
