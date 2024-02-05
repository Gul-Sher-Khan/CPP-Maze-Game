// 22i-2637 Gulsher Khan 22i-8791 Ahsan Faraz

#include <windows.h>
#include <conio.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
// Function for cursor position x,y
void gotoxy(int x, int y)
{
    COORD CursorPosition;
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
// Function for stting cursor
void setcursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 50;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}
// Getting keys as input to move our car
char getInput()
{
    char c = getch();
    if (c == 'w' || c == 'a' || c == 's' || c == 'd' || c == 'p')
        return c;
    else
        return getInput();
}