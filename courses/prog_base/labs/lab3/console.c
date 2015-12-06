#include "behavior.h"
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <tchar.h>
#include <conio.h>
//#include <strsafe.h>

int userLen;

void setCursorPosition(int x, int y) {
	COORD myCoord = { x, y };
	HANDLE cnsHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(cnsHndlr, myCoord);
}

void setTextColor(int color) {
	HANDLE cnsHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(cnsHndlr, color);
}

void drawRectangle(int xStart, int xEnd, int yStart, int yEnd, int color) {
	int i, j;
	setTextColor(color);
	for (i = xStart; i <= xEnd; i++) {
		for (j = yStart; j <= yEnd; j++) {
			setCursorPosition(i, j);
			printf(" ");
		}
	}
}

void drawCoolBorders(int xStart, int xEnd, int yStart, int yEnd, int color) {
	int i;
	setTextColor(color);
	for (i = xStart; i < xEnd + 1; i++) {
		setCursorPosition(i, yStart);
		putchar('*');
		setCursorPosition(i, yEnd);
		putchar('*');
	}
	for (i = yStart; i < yEnd; i++) {
		setCursorPosition(xStart, i);
		putchar('*');
		setCursorPosition(xEnd, i);
		putchar('*');
	}
}

void drawGreetings(char *myText [], int len) {
	int i;
	userLen = 0;
	char buffer[20];
	char *userInputLine = buffer;

	//Set window size.
	SMALL_RECT windowSize = { 0 , 0 , 79 , 49 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

	//Draw field for inputing data.
	drawRectangle(10, 70, 5, 20, 0x808080);
	drawCoolBorders(10, 70, 5, 20, BACKGROUND_GREEN);

	//Set how much strings user wants to type
	setTextColor(0x808080);
	setCursorPosition(13, 7);
	printf("How much strings do you want to type in? (less than %d)", len + 1);
	setCursorPosition(20, 8);
	puts("Enter pls:");
	setCursorPosition(30, 8);
	scanf("%d", &userLen);
	while (userLen > len) {
		if (userLen > len) {
			setCursorPosition(23, 12);
			puts("Sorry. No.");
			Sleep(1000);
		}
		drawRectangle(11, 69, 6, 19, 0x808080);
		setCursorPosition(15, 7);
		printf("How much strings do you want to type in? (less than %d)", len + 1);
		setCursorPosition(20, 8);
		puts("Enter pls:");
		setCursorPosition(30, 8);
		scanf("%d", &userLen);
	}

	//Add user input to *myText[]
	drawRectangle(11, 69, 6, 19, 0x808080);
	setCursorPosition(18, 7);
	printf("Please, enter your %d lines with max 20 length", userLen);
	setTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	for (i = 0; i < userLen; i++) {
		setCursorPosition(39, 9 + i);
		printf("|");
	}
	setTextColor(0x00 | 0x808080);
	gets (buffer);
	for (i = 0; i < userLen; i++) {
		setCursorPosition(17, 9 + i);
		printf("%d)",i+1);
		setCursorPosition(20, 9 + i);
		gets(buffer);
		myText[i] = (char*) calloc(20, sizeof(char));
		strcpy(myText[i], buffer);
	}
}

void drawConsole(char *myText [], int len) {

	drawGreetings(myText, len);

	int i;
	char userChoice[20];

	//Draw field for *myText[]
	setTextColor(0x00);
	system("cls");
	drawRectangle(5, 75, 3, 20, 0x808080);
	drawCoolBorders(5, 75, 3, 21, BACKGROUND_GREEN);
	setTextColor(BACKGROUND_GREEN);
	for (i = 3; i < 21; i++) {
		setCursorPosition(40, i);
		putchar('*');
	}
	setCursorPosition(13, 5);
	printf("Your default strings");
	setCursorPosition(51, 5);
	printf("Result of actions");
	setTextColor(0x00 | 0x808080);

	//Draw *myText[] - the user`s input
	for (i = 0; i < userLen; i++) {
		setCursorPosition(9, 7 + i);
		if (i == 9) {
			printf("10)|");
			break;
		}
		printf("%d) |", i + 1);
	}
	for (i = 0; i < userLen; i++) {
		setCursorPosition(14, 7 + i);
		printf("%s", myText[i]);
	}
	//User behavior - commands mostly
	setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY | 0x00);
	setCursorPosition(10, 24);
	printf("Please, enter your command! \"help\" command for more info. ");
	while (1) {
		drawRectangle(0, 79, 26, 40, 0x00);
		drawRectangle(42, 74, 6, 19, 0x808080);
		setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		setCursorPosition(5, 26);
		printf(">>");
		setCursorPosition(8, 26);
		scanf("%s", userChoice);
		//help action
		if (strcmp(userChoice, "help") == 0) {
			setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY| 0x00);
			setCursorPosition(8, 27); printf("Commands to help you:\n");
			setCursorPosition(8, 28); printf("1) help - shows help\n");
			setCursorPosition(8, 29); printf("2) order - print sorted lengthes of strings.\n");
			setCursorPosition(8, 30); printf("3) longest - print the longest string.\n");
			setCursorPosition(8, 31); printf("4) shortest - print the shortest string.\n");
			setCursorPosition(8, 32); printf("5) random - randomise strings with N length\n");
			setCursorPosition(8, 33); printf("6) swap - swap the first longest and the last shortest lines\n");
			setCursorPosition(8, 34); printf("7) lessthan - print all lines that are less than value\n");
			setCursorPosition(8, 35); printf("8) morethan - print all lines that are bigger than value\n");
			setCursorPosition(8, 36); printf("9) words - the number of words in each line\n");
			setCursorPosition(8, 37); printf("10) findnum - check all lines if they consist of digits only\n");
			setCursorPosition(8, 39); printf("Press any key to continue:)");
			getch();
		}
		//lengthes of string by desc order
		else if (strcmp(userChoice, "order") == 0) {
			setTextColor(0x00 | 0x808080);
			int i, lengthOrderBuff[10];
			lengthOrder(myText, userLen, lengthOrderBuff);
			setCursorPosition(44, 7);
			printf("Lengthes of strings in order: ");
			for (i = 0; i < userLen; i++) {
				setCursorPosition(45, 9 + i);
				printf("%d", lengthOrderBuff[i]);
			}
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 28); printf("Ready! Press any key to continue.");
			getch();
		}
		//get the longest line
		else if (strcmp(userChoice, "longest") == 0) {
			char *userLongestResult = getLongest(myText, userLen);
			setTextColor(0x00 | 0x808080);
			setCursorPosition(44, 7);
			printf("The longest string is:");
			setCursorPosition(47, 9);
			puts(userLongestResult);
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 28); printf("Ready! Press any key to continue.");
			getch();
		}
		//get the shortest line
		else if (strcmp(userChoice, "shortest") == 0) {
			char *userLongestResult = getShortest(myText, userLen);
			setTextColor(0x00 | 0x808080);
			setCursorPosition(44, 7);
			printf("The shortest string is:");
			setCursorPosition(47, 9);
			puts(userLongestResult);
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 28); printf("Ready! Press any key to continue.");
			getch();
		}
		//randomize strings
		else if (strcmp(userChoice, "random") == 0) {
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			int randomNUserChoice, i;
			char *randomTempStrArr[10];
			for (i = 0; i < userLen; i++) {
				randomTempStrArr[i] = (char*) calloc(20, sizeof(char));
			}
			setCursorPosition(8, 28);
			printf("Please, enter N value: | 0 < N < 11 pls");
			setCursorPosition(8, 29);
			printf(">>");
			setCursorPosition(11, 29);
			scanf("%d", &randomNUserChoice);
			getchar();
			setCursorPosition(8, 30);
			printf("Do you want leave matrix randomised? Y/N");
			setCursorPosition(8, 31);
			printf(">>");
			setCursorPosition(11, 31);
			char c = (char) getchar();
			if (c == 'Y') {
				setTextColor(0x00 | 0x808080);
				fillRandom(myText, userLen, randomNUserChoice);
				setCursorPosition(44, 7);
				printf("The randomised array is:");
				for (i = 0; i < userLen; i++) {
					setCursorPosition(47, 9 + i);
					printf("%s", myText[i]);
				}
			}
			else if (c == 'N') {
				setTextColor(0x00 | 0x808080);
				fillRandom(randomTempStrArr, userLen, randomNUserChoice);
				setCursorPosition(44, 7);
				printf("The randomised array is:");
				for (i = 0; i < userLen; i++) {
					setCursorPosition(47, 9 + i);
					printf("%s", randomTempStrArr[i]);
				}
			}
			else {
				setTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY | 0x808080);
				setCursorPosition(47, 9);
				printf("INVALID INPUT ERROR");
				setTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
				setCursorPosition(8, 34);
				printf("ERROR");
			}
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 35); printf("Ready! Press any key to continue.");
			getch();
		}
		//swap first shortest and last longest lines
		else if (strcmp(userChoice, "swap") == 0) {
			setTextColor(0x00 | 0x808080);
			swapShLn(myText, userLen);
			setCursorPosition(44, 7);
			printf("The swapped array is:");
			for (i = 0; i < userLen; i++) {
				setCursorPosition(47, 9 + i);
				printf("%s", myText[i]);
			}
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 28); printf("Ready! Press any key to continue.");
			getch();
		}
		//print out all lines that are less than Value
		else if (strcmp(userChoice, "lessthan") == 0) {
			int i;
			char *tempStrArrForLessThan[10];
			int userLessThanValue;
			for (i = 0; i < userLen; i++) {
				tempStrArrForLessThan[i] = (char*) calloc(20, sizeof(char));
			}
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 28);
			printf("Please, enter value: | >0 pls");
			setCursorPosition(8, 29);
			printf(">>");
			setCursorPosition(11, 29);
			scanf("%d", &userLessThanValue);
			lessThan(myText, userLen, userLessThanValue, tempStrArrForLessThan);
			setTextColor(0x00 | 0x808080);
			setCursorPosition(44, 7);
			printf("Strings, less than %d:", userLessThanValue);
			for (i = 0; i < userLen; i++) {
				setCursorPosition(47, 9 + i);
				printf("%s", tempStrArrForLessThan[i]);
			}
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 35); printf("Ready! Press any key to continue.");
			getch();
		}
		//print out all lines that are more than Value
		else if (strcmp(userChoice, "morethan") == 0) {
			int i;
			char *tempStrArrForMoreThan[10];
			int userMoreThanValue;
			for (i = 0; i < userLen; i++) {
				tempStrArrForMoreThan[i] = (char*) calloc(20, sizeof(char));
			}
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 28);
			printf("Please, enter value: | >0 pls pls");
			setCursorPosition(8, 29);
			printf(">>");
			setCursorPosition(11, 29);
			scanf("%d", &userMoreThanValue);
			moreThan(myText, userLen, userMoreThanValue, tempStrArrForMoreThan);
			setTextColor(0x00 | 0x808080);
			setCursorPosition(44, 7);
			printf("Strings, more than %d:", userMoreThanValue);
			for (i = 0; i < userLen; i++) {
				setCursorPosition(47, 9 + i);
				printf("%s", tempStrArrForMoreThan[i]);
			}
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 35); printf("Ready! Press any key to continue.");
			getch();
		}

		//words - count how much words are in each line!
		else if (strcmp(userChoice, "words") == 0) {
			int tempArrForWords[10], i;
			wordsCount(myText, userLen, tempArrForWords);
			setTextColor(0x00 | 0x808080);
			setCursorPosition(44, 7);
			printf("Words in each line:");
			for (i = 0; i < userLen; i++) {
				setCursorPosition(47, 9 + i);
				if (tempArrForWords[i] == 1) {
					printf("Line %d has 1 word", i + 1);
				}
				else {
					printf("Line %d has %d words", i + 1, tempArrForWords[i]);
				}

			}
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 28); printf("Ready! Press any key to continue.");
			getch();
		}
		//findnum - check all lines if they consist of digits only
		else if (strcmp(userChoice, "findnum") == 0) {
			int i, tempVarForFindNum;
			setTextColor(0x00 | 0x808080);
			setCursorPosition(44, 7);
			printf("Lines with digits only");
			for (i = 0; i < userLen; i++) {
				tempVarForFindNum = findNumInStr(myText, userLen, i);
				if (tempVarForFindNum == 0) {
					setCursorPosition(47, 9 + i);
					printf("Not a \"number\" line");
				}
				else {
					setCursorPosition(47, 9 + i);
					printf("%d", tempVarForFindNum);
				}
			}
			setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0x00);
			setCursorPosition(8, 28); printf("Ready! Press any key to continue.");
			getch();
		}
		//quit action
		else if(strcmp(userChoice, "exit") == 0){

			int i;
			for (i = 0; i < len; i++) {
				free(myText[i]);
			}
			return EXIT_SUCCESS;
		}
		//invalid action
		else {
			setTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
			setCursorPosition(8, 28); printf("Invalid input, sorry.");
			setCursorPosition(8, 29); printf("Press any key to continue");
			getch();
		}
	}
}

