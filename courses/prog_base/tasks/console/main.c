#include <stdio.h>
#include <stdlib.h>
#include <windows.h>



COORD moveUP (COORD pos, int border) {
    int color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1) {
        if (pos.Y==border) break;
        SetConsoleCursorPosition(hConsole, pos);
        switch (pos.X - pos.Y) {
       case 0: case 55: color = BACKGROUND_RED;
        SetConsoleTextAttribute(hConsole, color); break;
        case 1 ... 54: color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color); break;

        default: color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color); break;
        }
        printf("*");
        Sleep(10);
        pos.Y--;
    }
    return pos;
}

COORD moveDOWN (COORD pos, int border) {
    int color;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1) {
        if (pos.Y==border) break;
        SetConsoleCursorPosition(hConsole, pos);
               switch (pos.X - pos.Y) {
      case 0: case 55: color = BACKGROUND_RED;
        SetConsoleTextAttribute(hConsole, color); break;
        case 1 ... 54: color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color); break;

        default: color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color); break;
        }
        printf("*");
        Sleep(10);
        pos.Y++;
    }
    return pos;
    }

COORD moveRIGHT (COORD pos, int border) {
    int color;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1) {
        if (pos.X == border) break;
        SetConsoleCursorPosition(hConsole, pos);
               switch (pos.X - pos.Y) {
        case 0: case 55: color = BACKGROUND_RED;
        SetConsoleTextAttribute(hConsole, color); break;
        case 1 ... 54: color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color); break;

        default: color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color); break;
        }
        printf("*");
        Sleep(10);
        pos.X++;
    }
    return pos;
}

COORD moveLEFT (COORD pos, int border) {
    int color;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1) {
        if (pos.X == border) break;
        SetConsoleCursorPosition(hConsole, pos);
               switch (pos.X - pos.Y) {
       case 0: case 55: color = BACKGROUND_RED;
        SetConsoleTextAttribute(hConsole, color); break;
        case 1 ... 54: color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color); break;

        default: color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color); break;
        }
        printf("*");
        Sleep(10);
        pos.X--;
    }
    return pos;
}

int main()
{

    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_red = BACKGROUND_RED;
    int color_white = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    int rBorder=79,lBorder=0,uBorder=0,dBorder=23;
    pos.X=0;
    pos.Y=24;
    int i;
    for (i=0; i<14; i++) {
        pos = moveRIGHT(pos, rBorder);
        rBorder--;
        if (rBorder == 66) {
        printf("*");
        break;
    }
        pos = moveUP(pos, uBorder);
        uBorder++;
        pos = moveLEFT(pos, lBorder);
        lBorder++;
        pos = moveDOWN(pos, dBorder);
        dBorder--;
    }

    pos.X = 0;
    pos.Y = 26;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);


    return 0;
}
