#include "Utils.h"

using namespace std;

void setTextColor(int foreground_color, int background_color) {
	int color = foreground_color | background_color * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setTextColor(int foreground_color) {
	setTextColor(foreground_color, 0);
}

// function definition -- requires windows.h
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
// function that put the cursor in the right position
void gotoxyAux(int col, int row)
{
	gotoxy((BASE_COL + (col*CELL_SIZE_COL)), (BASE_ROW + (row*CELL_SIZE_ROW)));
}

void clearScreen() {
	system("cls");
}

bool converStringToInt(int *backInt, const char * str) {

	int result = 0;
	bool isNumber = true;

	while (*str != '\0') {
		if ((*str < '0') || (*str > '9')) {
			isNumber = false;
		}

		result = (result * 10) + ((*str) - '0');
		str++;
	}

	if (isNumber == true) {
		*backInt = result;
	}
	return isNumber;
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}