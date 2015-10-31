#include <string.h>
#include <ctype.h>

char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr) {
	*resultStr = NULL; //Обнуляємо на випадок, якщо там сміття
	int i;
	for (i = 0; i < linesNum; ++i) {
		char tempStr[100]; // Сюди записуємо букви у нижньому регітсрі
		strcpy(tempStr, " ");
		int upper = 0; // Сюди записуємо кількість букв у верхньому регістрі
		int lower = 0; // Сюди записуємо кількість букв у нижньому регістрі

		while (*textLines[i]) // Виконуємо доки вказівник вказує на існуючу комірку памяті
		{
			if (isupper(*textLines[i])) {
				upper++;
			}
			else if (islower(*textLines[i])) {
				lower++;
				strncat(tempStr, &(*textLines[i]), 1);
			}
			*textLines[i]++; //Перевдимо вказівник на наступну область памяті
		}
		if (lower == upper) {
			sprintf(resultStr, "%d%s", lower, tempStr);
		}
	}
	if (resultStr != NULL && resultStr[0] != '\0') {
		return resultStr;
	}
	else
	{
		sprintf(resultStr, "0 NULL %s", extraStr);
		return resultStr;
	}
}
