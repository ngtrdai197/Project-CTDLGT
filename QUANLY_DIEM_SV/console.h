#ifndef CONSOLE_H
#define CONSOLE_H

#include<windows.h>
#include <iomanip>
#include<string>
#include <conio.h>


#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7


#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_Enter   13
#define key_none	-1
#define key_bkspace 8
#define key_tab		9

using namespace std;


void DisableMaxiMize() {
	char title[] = "Dai Nguyen";
	SetConsoleTitle(TEXT("Dai Nguyen"));

	while (FindWindowA(NULL, title) == NULL);
	SetWindowLong(FindWindowA(NULL, title), GWL_STYLE,
		GetWindowLong(FindWindowA(NULL, title), GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void SizeConsole(SHORT Width, SHORT height)
{
	HANDLE stdhandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT SizeW = { 0,0,Width - 1,height - 1 };
	COORD sizebuff = { Width,height };
	BOOL BSize = SetConsoleWindowInfo(stdhandle, true, &SizeW);
	SetConsoleScreenBufferSize(stdhandle, sizebuff);
	if (!BSize) SetConsoleWindowInfo(stdhandle, true, &SizeW);
}

void SetSizeWindows(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, width, height, TRUE);
}

void gotoXY(short x, short y) {
	HANDLE stdhandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD info{
		x = x,y = y
	};
	SetConsoleCursorPosition(stdhandle, info);
}
void SetColor(int color) {
	HANDLE stdhandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(stdhandle, color);
}

int getX()//lay toa do x hien tai cua con tro console.
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
int getY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}


void rectagle(int x, int y, int width, int height) {
	gotoXY(x, y);
	cout << setfill((char)196);
	cout << char(218) << setw(width - 1) << char(191);
	cout << setfill(' ');
	for (int i = 1; i < height; i++)
	{
		gotoXY(x, y + i);
		cout << char(179) << setw(width - 1) << char(179);
	}
	gotoXY(x, y + height);
	cout << setfill((char)196);
	cout << char(192) << setw(width - 1) << char(217);

}

int inputKey()
{
	int key = _getch();
	if (key == 224)	// special key
	{
		key = _getch();
		return key + 1000;
	}
	return key;
}

string TextInput(string text, int key, int limit) {
	switch (key)
	{
	default:
		if (key > 31 && key < 127) {

			if (text.length() < limit) {
				text += key;
			}
		}
		break;
	}
	return text;
}

#endif // !CONSOLE_H
