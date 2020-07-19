#ifndef CONSOLE_H
#define CONSOLE_H

#include<windows.h>
#include <iomanip>
#include<string>
#include <conio.h>


#define color_black 0x0000
#define color_darkblue 0x0001
#define color_darkgreen 0x0002
#define color_darkcyan 0x0003
#define color_darkred 0x0004
#define color_darkpink 0x0005
#define color_darkyellow 0x0006
#define color_darkwhite 0x0007
#define color_grey 0x0008
#define color_blue 0x0009
#define color_green 0x000a
#define color_cyan 0x000b
#define color_red 0x000c
#define color_pink 0x000d
#define color_yellow 0x000e
#define color_white 0x000f

#define colorbk_black 0x0000
#define colorbk_darkblue 0x0010
#define colorbk_darkgreen 0x0020
#define colorbk_darkcyan 0x0030
#define colorbk_darkred 0x0040
#define colorbk_darkpink 0x0050
#define colorbk_darkyellow 0x0060
#define colorbk_darkwhite 0x0070
#define colorbk_grey 0x0080
#define colorbk_blue 0x0090
#define colorbk_green 0x00a0
#define colorbk_cyan 0x00b0
#define colorbk_red 0x00c0
#define colorbk_pink 0x00d0
#define colorbk_yellow 0x00e0
#define colorbk_white 0x00f0


#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_Enter   13
#define key_none	-1
#define key_bkspace 8
#define key_tab		9
#define key_esc     27

using namespace std;
auto whandConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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

void clrscr(int x, int y,int col, int row, CHAR ch,int color = color_black) {
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



void ReadBlockChar(CHAR_INFO* &Arraych,
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
