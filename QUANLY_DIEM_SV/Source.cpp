#include "Menu.h"
using namespace std;

int main()
{
	AppContext context;
	InitTree(context.tree);
	ReadListLopTinChi(context.tree, context.nLTC);
	ReadFileSinhVien(context.ds_sv);
	Read_File_MonHoc(context.ds_mh);
	RemoveScrollbar();
	srand(time(NULL));
	int isLogged = openLogin(context);
	if (isLogged == 1) {
		DrawMainLayout(context.currentUser);
		ProcessConrtol(context);
	}
	return 0;
}