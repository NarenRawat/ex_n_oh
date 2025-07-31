#include <windows.h>
#include <stdio.h>

#include "console.h"

static HANDLE stdout_handle;
static HANDLE stdin_handle;
static UINT out_code_page;
static DWORD stdin_mode;

static int get_events_count() {
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

void get_console_size(int *rows, int *cols) {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;

    GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);

    *rows = buffer_info.dwSize.Y;
    *cols = buffer_info.dwSize.X;
}

void init_console(void) {
    stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    stdin_handle = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(stdin_handle, &stdin_mode);
    SetConsoleMode(stdin_handle, stdin_mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    out_code_page = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
}

void cleanup_console(void) {
    SetConsoleOutputCP(out_code_page);
    SetConsoleMode(stdin_handle, stdin_mode);
}

