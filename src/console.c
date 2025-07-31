#include <windows.h>
#include <stdio.h>

#include "console.h"

HANDLE stdout_handle;
UINT out_code_page;

void get_console_size(int *rows, int *cols) {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;

    GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);

    *rows = buffer_info.dwSize.Y;
    *cols = buffer_info.dwSize.X;
}

void init_console(void) {
    stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    out_code_page = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
}

void cleanup_console(void) {
    SetConsoleOutputCP(out_code_page);
}

