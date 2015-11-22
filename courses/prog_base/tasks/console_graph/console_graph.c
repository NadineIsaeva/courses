#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

void drawWhiteConsole(HANDLE hConsole, COORD pos);
void drawAxes(HANDLE hConsole, COORD pos, int OX, int OY, int zoom);
void drawFirstGraph(HANDLE hConsole, COORD pos, int OX, int OY, int zoom);
void drawSecondGraph(HANDLE hConsole, COORD pos, int OX, int OY, int zoom);

void drawAxes(HANDLE hConsole, COORD pos, int OX, int OY, int zoom)
{
            if (OX > 79)
                OX = 79;
            if (OX < 0)
                OX = 0;
            if (OY > 24)
                OY = 24;
            if (OY < 0)
                OY = 0;
            pos.X = OX;
            if (zoom < 1)
                zoom = 1;
            int color =  FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN;
            SetConsoleTextAttribute(hConsole, color);

            for (pos.Y = 0; pos.Y < 25; pos.Y++)
            {
                SetConsoleCursorPosition(hConsole, pos);
                if (pos.Y % zoom == OY % zoom)
                {
                    printf("+");
                }
                else
                {
                    printf("|");
                }
            }
            pos.Y = OY;
            for (pos.X = 0; pos.X < 80; pos.X++)
            {
                SetConsoleCursorPosition(hConsole, pos);
                if (pos.X % zoom == OX % zoom)
                {
                    printf("+");
                }

                else
                {
                    printf("-");
                }
            }
}
void drawWhiteConsole(HANDLE hConsole, COORD pos)
{
	int i, j;
	int color = FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN;
	SetConsoleTextAttribute(hConsole, color);

	for (i = 0; i < 25; i++)
		for (j = 0; j < 80; j++)
		{
		    pos.Y = i;
			pos.X = j;
			SetConsoleCursorPosition(hConsole, pos);
				putchar(' ');
		}
}

    void drawFirstGraph(HANDLE hConsole, COORD pos, int OX, int OY, int zoom)
    {
        int color = FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);

        double k;
	    if (zoom > 0)
		k = (double)zoom;

		else
		k = 1 / (1 - (double)zoom);
		for (pos.X = 0; pos.X < 80; pos.X++)
        {
            pos.Y = k*(-2/(4*((pos.X - OX) / k )- 1) - 1) + OY;
            if (pos.Y > -1 && pos.Y < 25)
            {
                SetConsoleCursorPosition(hConsole, pos);
                printf(" ");
            }
        }
        color = FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color);
        pos.X = 0;
        pos.Y = 0;
        SetConsoleCursorPosition(hConsole, pos);
        printf("The first graph: F(x) = -2 / (4*x - 1) - 1");
    }

    void drawSecondGraph(HANDLE hConsole, COORD pos, int OX, int OY,  int zoom)
    {
        int color = FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
        double k;
        if (zoom > 0)
            k = (double)zoom;
        else
            k = 1 / (1 - (double)zoom);
            for (pos.X = 0; pos.X < 80; pos.X++)
            {
                pos.Y = -round(cos(pow((pos.X - OX)/k,2)) + pow(sin(2*(pos.X - OX)/k),2) + 1) + OY;
                if (pos.Y > -1 && pos.Y < 25)
                {
                    SetConsoleCursorPosition(hConsole, pos);
                    printf(" ");
                }
            }
        	color = FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
            SetConsoleTextAttribute(hConsole, color);
            pos.X = 0;
            pos.Y = 0;
            SetConsoleCursorPosition(hConsole, pos);
            printf("The second graph: F(x) = cos(x*x) + pow(sin(2*x),2) + 1");
}

int main(void)
{
    int OX = 39;
	int OY = 13;
    int zoom = 5;
	int exitValue = 0;
	int graph = 1;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	char ch;
	while(exitValue == 0)
    {
        drawWhiteConsole(hConsole, pos);
		drawAxes(hConsole, pos, OX, OY, zoom);
		if (graph % 2 == 1)
			drawFirstGraph(hConsole, pos, OX, OY, zoom);
		else
			drawSecondGraph(hConsole, pos, OX, OY, zoom);
        printf("\nw - up, s - down, d - left\na - right, + zoom in, - zoom out\nc - change graph, x - exit");
        ch = getch();
		switch (ch)
		{
		    case 'x' : exitValue = 1; break;
            case '+' : zoom++; break;
			case '-' : zoom--; break;
		    case 'c' : graph++; break;
			case 'd' : OX--; break;
			case 'a' : OX++; break;
			case 's' : OY++; break;
			case 'w' : OY--; break;
			default : break;
		}
    }
		int color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
        SetConsoleTextAttribute(hConsole, color);
        pos.Y = 25;
        SetConsoleCursorPosition(hConsole, pos);
        puts(" ");
        return EXIT_SUCCESS;
}
