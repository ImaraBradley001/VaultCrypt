#include <Windows.h>
#include <progressBar.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void changeColor(int desiredColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void showcursor(int CursorVisble) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 25;
    info.bVisible = CursorVisble;
    SetConsoleCursorInfo(consoleHandle, &info);
}
