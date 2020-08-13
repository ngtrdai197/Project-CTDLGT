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
	openLogin(context);
	if (context.currentUser != NULL) {
		DrawMainLayout("");
		ProcessConrtol(context);
	}
	return 0;
}