#include <string.h>
#include <ctype.h>

char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr) {
	*resultStr = NULL;
	int i;
	for (i = 0; i < linesNum; ++i) {
		char tempStr[100];
		strcpy(tempStr, " ");
		int upper = 0;
		int lower = 0;

		while (*textLines[i])
		{
			if (isupper(*textLines[i])) {
				upper++;
			}
			else if (islower(*textLines[i])) {
				lower++;
				strncat(tempStr, &(*textLines[i]), 1);
			}
			*textLines[i]++;
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
