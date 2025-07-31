#include <windows.h>
#include <stdio.h>

#include "console.h"
#include "vector2d.h"

static HANDLE stdout_handle;
static HANDLE stdin_handle;
static UINT out_code_page;
static DWORD stdin_mode;

void init_console(void) {
    printf("\e[?1049h");
    printf("\e[?25l");


    stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    stdin_handle = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(stdin_handle, &stdin_mode);
    SetConsoleMode(stdin_handle, stdin_mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    out_code_page = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
}

static int get_events_count(void) {
    DWORD count;
    GetNumberOfConsoleInputEvents(stdin_handle, &count);
    return count;
}

int get_input_code(void) {
    int event_count = get_events_count();

    if (event_count == 0) {
        return 0;
    }

    INPUT_RECORD records;
    DWORD events;

    for (int i = 0; i < event_count; i++) {
        ReadConsoleInput(stdin_handle, &records, 1, &events);

        if (records.EventType == KEY_EVENT && records.Event.KeyEvent.bKeyDown) {
            return records.Event.KeyEvent.wVirtualKeyCode;
        }
    }

    return 0;
}

void get_console_size(Vector2D *p_vec) {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;

    GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);

    p_vec->x = buffer_info.dwSize.X;
    p_vec->y = buffer_info.dwSize.Y;
}


void cleanup_console(void) {
    SetConsoleOutputCP(out_code_page);
    SetConsoleMode(stdin_handle, stdin_mode);

    printf("\e[?25h");
    printf("\e[?1049l");
}

