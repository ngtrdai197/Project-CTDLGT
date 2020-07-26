
#include "Menu.h"


using namespace std;


int main()
{
	//string h[4];

	//DrawFormInput(0, 0, 60, h, 4);
	AppContext context;
	InitTree(context.tree);
	ReadListLopTinChi(context.tree, context.ds_sv_original);
	Read_File_MonHoc(context.ds_mh);
	srand(time(NULL));
	//SetColor(bk_blue | red);
	//string a = openLogin();
	//if (a.length() > 0) {
	DrawMainLayout("");
	ProcessConrtol(context);
	//}
	/*DS_SINH_VIEN ds_sv;
	Init_DS_Sinh_Vien(ds_sv);
	ReadFileSinhVien(ds_sv);
	Show_DS_Sinh_Vien(ds_sv);
	NODE_SINH_VIEN* newSv = Input_Sinh_Vien(ds_sv);
	bool exist = CheckExistLop(newSv->data.MALOP);
	if (!exist) {
		cout << "Insert new class into list";
		InsertLopIntoDSLop(newSv->data.MALOP);
	}
	cout << "\m ========== DS AFTER UPDATED ==============\n";
	InsertAndSortSvIntoDS(ds_sv, newSv);
	UpdateListStudentToFile(ds_sv);
	Show_DS_Sinh_Vien(ds_sv);*/
	/*DS_DANG_KY ds_dangky;
	int n = 0;
	Init_DS_Dang_Ky(ds_dangky);
	ReadFileDS_DANG_KY(ds_dangky);
	Show_DS_Dang_Ky(ds_dangky);*/

	//ConvertTreeToArray(context.tree, context.ds, context.nLTC);
	//ShowDSLopTinChi(context.ds, n);
	//ShowDSSVDangKyLTC(ds, n);
	//Lop_Tin_Chi* update = InputUpdateTree();
	//UpdateNodeOfTree(context.tree, update);
	//n = 0;
	//ConvertTreeToArray(tree, ds, n);
	//UpdateListLopTinChiToFile(ds, n);
	//ShowDSLopTinChi(ds, n);
	/*InsertLopTCIntoTree(tree);
	n = 0;
	ConvertTreeToArray(tree, ds, n);
	UpdateListLopTinChiToFile(ds, n);
	ShowDSLopTinChi(ds, n);*/
	/*int x;
	cout << "Nhap ma lop tin chi can xoa:"; cin >> x;
	RemoveNodeOfTree(tree, x);
	n = 0;
	ConvertTreeToArray(tree, ds, n);*/
	//ShowDSLopTinChi(ds, n);
	//cout << "=========== DS LOP TIN CHI SAU KHI XOA =============\n";
	//Show_DS_Sinh_Vien(ds_sv);
	/*UpdateListLopTinChiToFile(ds, n);
	ShowDSLopTinChi(ds, n);*/
	/*int x;
	cout << "Nhap ma lop tin chi can xoa:"; cin >> x;
	RemoveNodeOfTree(tree, x);

	n = 0;
	ConvertTreeToArray(tree, ds, n);
	for (int i = 0; i < n; i++)
	{
		UpdateListLopTinChiToFile(ds[i], n);
	}
	ShowDSLopTinChi(ds, n);*/

	//delete[]ds;
	/*DS_MON_HOC ds_mh;
	ds_mh.n = 0;
	Read_File_MonHoc(ds_mh);
	Show_DS_MonHoc(ds_mh);
	Insert_MonHoc(ds_mh);
	UpdateFileDSMonHoc(ds_mh);
	cout << "\n=========== List after insert =============\n";
	Show_DS_MonHoc(ds_mh);
	system("pause");*/
	return 0;
}