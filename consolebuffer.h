#ifndef CONSOLEBUFFER_H
#define CONSOLEBUFFER_H

#include "chartype.h"
#include <windows.h>

static struct __ConsoleBuffer {
    HANDLE WINAPI GetStdInputHandle();
    HANDLE WINAPI GetStdOutputHandle();
    void ClearStdOutput();
    void GotoXY(SHORT x, SHORT y);
    void WriteChar(CharType x);
    void SetConsoleSize(int x, int y, int cols, int lines);
    void SetConsoleSize(int cols, int lines);
    void SetColor(WORD x);
    void HideConsoleCursor();
    void ShowConsoleCursor();

    void *OnFront = nullptr;
} ConsoleBuffer;

#endif
