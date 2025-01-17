﻿#include "Menu.h"
using namespace std;

int main()
{
	RemoveScrollbar();
	srand(time(NULL));
	AppContext context;
	InitTree(context.tree);
	ReadListLopTinChi(context.tree, context.nLTC);
	ReadFileSinhVien(context.ds_sv);
	Read_File_MonHoc(context.ds_mh);
	int permission = openLogin(context);
	if (permission == -1) return 0;
	DrawMainLayout(context.currentUser, permission);
	if (!permission) {
		ProcessControlGV(context);
	}
	else {
		ProcessControl_SV(context);
	}
	return 0;
}