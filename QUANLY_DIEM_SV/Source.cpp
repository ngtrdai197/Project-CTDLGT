﻿#include "Menu.h"
using namespace std;

int main()
{
	AppContext context;
	InitTree(context.tree);
	ReadListLopTinChi(context.tree, context.nLTC);
	ReadFileSinhVien(context.ds_sv);
	Read_File_MonHoc(context.ds_mh);
	srand(time(NULL));
	//SetColor(bk_blue | red);
	//string a = openLogin();
	//if (a.length() > 0) {
	RemoveScrollbar();
	DrawMainLayout("");
	ProcessConrtol(context);
	return 0;
}