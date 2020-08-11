#ifndef CONSOLE_H
#define CONSOLE_H

#include<windows.h>
#include <iomanip>
#include <iostream>
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
#define key_F11		1133
#define key_F12		1134
#define key_F2		1060
#define key_F3		1061


void RemoveScrollbar();

int gettxtColor();

void SetColor(int color);

void WriteBlockChar(CHAR_INFO* charater,
	SHORT row, SHORT col,
	SHORT x, SHORT y);

void clrscr(int x, int y, int col, int row, CHAR ch, int color = color_black);

void ReadBlockChar(CHAR_INFO*& Arraych,
	SHORT row, SHORT col,
	SHORT x, SHORT y);

void DisableMaxiMize();

void SizeConsole(SHORT Width, SHORT height);

void SetSizeWindows(int width, int height);

void gotoXY(short x, short y);

int getX();
int getY();


void rectagle(int x, int y, int width, int height);

int inputKey();

std::string TextInput(std::string text, int key, int limit);



#endif // !CONSOLE_H
