#ifndef CONSOLE_CPP
#define CONSOLE_CPP

#ifndef CONSOLE_H
#include "console.h"
#endif

static HANDLE whandConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int gettxtColor()
{
	CONSOLE_SCREEN_BUFFER_INFO cisb;
	GetConsoleScreenBufferInfo(whandConsole, &cisb);
	return cisb.wAttributes;
}
void SetColor(int color) {
	HANDLE stdhandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(stdhandle, color);
}
void WriteBlockChar(CHAR_INFO* charater,
	SHORT row, SHORT col,
	SHORT x, SHORT y)
{
	COORD sizebuff = { col,row };
	COORD pos = { 0,0 };
	SMALL_RECT earea = { x,y,x + col ,y + row };
	WriteConsoleOutput(whandConsole, charater, sizebuff, pos, &earea);
	delete[] charater;
}

void clrscr(int x, int y, int col, int row, CHAR ch, int color) {
	int size = col * row;
	CHAR_INFO* charater = new CHAR_INFO[size];
	for (int i = 0; i < size; i++)
	{
		charater[i].Attributes = color;
		charater[i].Char.UnicodeChar = ch;
		charater[i].Char.AsciiChar = ch;
	}
	SetColor(color);
	WriteBlockChar(charater, row, col, x, y);
}

void ReadBlockChar(CHAR_INFO*& Arraych,
	SHORT row, SHORT col,
	SHORT x, SHORT y)
{
	CHAR_INFO* charater = new CHAR_INFO[row * col];
	COORD sizebuff = { col,row };
	COORD pos = { 0,0 };
	SMALL_RECT earea = { x,y,x + col - 1,y + row - 1 };
	ReadConsoleOutput(whandConsole, charater, sizebuff, pos, &earea);
	Arraych = charater;
}

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
	std::cout << std::setfill((char)196);
	std::cout << char(218) << std::setw(width - 1) << char(191);
	std::cout << std::setfill(' ');
	for (int i = 1; i < height; i++)
	{
		gotoXY(x, y + i);
		std::cout << char(179) << std::setw(width - 1) << char(179);
	}
	gotoXY(x, y + height);
	std::cout << std::setfill((char)196);
	std::cout << char(192) << std::setw(width - 1) << char(217);

}

int inputKey()
{
	int key = _getch();
	if (key == 224 || key == 0)	// special key
	{
		key = _getch();
		return key + 1000;
	}
	return key;
}

std::string TextInput(std::string text, int key, int limit) {
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

#endif // !CONSOLE_CPP
