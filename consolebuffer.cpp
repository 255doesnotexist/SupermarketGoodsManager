#include "consolebuffer.h"


HANDLE WINAPI __ConsoleBuffer::GetStdInputHandle() {
    return GetStdHandle(STD_INPUT_HANDLE);
}
HANDLE WINAPI __ConsoleBuffer::GetStdOutputHandle() {
    return GetStdHandle(STD_OUTPUT_HANDLE);
}
void __ConsoleBuffer::ClearStdOutput() {
    HANDLE hConsole = GetStdOutputHandle();
    COORD coordScreen = { 0, 0 };    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) { // Receive number of characters written
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten)) { // Receive number of characters written
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void __ConsoleBuffer::GotoXY(SHORT x, SHORT y) {
    SetConsoleCursorPosition(__ConsoleBuffer::GetStdOutputHandle(), (COORD) {
        x, y
    });
}

void __ConsoleBuffer::WriteChar(CharType x) {
    DWORD lpNumberOfCharsWritten;
    SetConsoleTextAttribute(__ConsoleBuffer::GetStdOutputHandle(), x.Attribute);
    WriteConsoleW(__ConsoleBuffer::GetStdOutputHandle(), &x.WideChar, 1, &lpNumberOfCharsWritten, NULL);
}

void __ConsoleBuffer::SetConsoleSize(int x, int y, int cols, int lines) {
    HANDLE hOut;
    CONSOLE_FONT_INFO consoleCurrentFont;
    COORD bufferSize, fontSize;
    HWND hWnd;
    //Set console buffer size
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFont(hOut, false, &consoleCurrentFont);
    fontSize = GetConsoleFontSize(hOut, consoleCurrentFont.nFont);
    bufferSize.X = cols;
    bufferSize.Y = lines;
    SetConsoleScreenBufferSize(hOut, bufferSize);
    //Set console window size
    hWnd = GetConsoleWindow();
    MoveWindow(hWnd, x, y, (cols + 4)*fontSize.X, (lines + 2)*fontSize.Y, true);
}

void __ConsoleBuffer::SetConsoleSize(int cols, int lines) {
    RECT rt;
    GetWindowRect(GetConsoleWindow(), &rt);
    this -> SetConsoleSize(rt.left, rt.top, cols, lines);
}

void __ConsoleBuffer::SetColor(WORD color) {
    SetConsoleTextAttribute(__ConsoleBuffer::GetStdOutputHandle(), color);
    SetConsoleTextAttribute(__ConsoleBuffer::GetStdInputHandle(), color);
}

void __ConsoleBuffer::HideConsoleCursor() {
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(__ConsoleBuffer::GetStdOutputHandle(), &CursorInfo);
    CursorInfo.bVisible = false; 
    SetConsoleCursorInfo(__ConsoleBuffer::GetStdOutputHandle(), &CursorInfo);
}

void __ConsoleBuffer::ShowConsoleCursor() {
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(__ConsoleBuffer::GetStdOutputHandle(), &CursorInfo);
    CursorInfo.bVisible = true; 
    SetConsoleCursorInfo(__ConsoleBuffer::GetStdOutputHandle(), &CursorInfo);
}
