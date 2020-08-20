
#ifndef STRUCTURE_H
#include "Structure.h"
#endif


#ifndef STRUCTURE_CPP
#define STRUCTURE_CPP


// ===== BEGIN HELPER =====
bool CheckExistMSSV(DS_SINH_VIEN ds_sv, char* massv)
{
	bool exist = false;
	if (ds_sv.totalSv == 0) return false;
	for (NODE_SINH_VIEN* k = ds_sv.pHead; k != NULL; k = k->pNext)
	{
		if (_strcmpi(k->data.MASV, massv) == 0)
		{
			exist = true;
			break;
		}
	}
	return exist;
}
bool CheckExistMaMH(DS_MON_HOC ds_mh, char* maMH)
{
	bool exist = false;
	for (int i = 0; i < ds_mh.n; i++)
	{
		if (_strcmpi(ds_mh.ds[i]->MAMH, maMH) == 0)
		{
			exist = true;
			break;
		}
	}
	return exist;
}
bool CheckExistMaLTC(TREE tree, int maLopTc) {
	if (tree == NULL)return false;
	if (tree->data.MALOPTC == maLopTc) {
		return false;
	}
	else if (tree->data.MALOPTC > maLopTc) {
		CheckExistMaLTC(tree->pRight, maLopTc);
	}
	else if (tree->data.MALOPTC < maLopTc) {
		CheckExistMaLTC(tree->pLeft, maLopTc);
	}
}
void Trim(string& str) {
	cout << str;
	while (str[0] == ' ')
	{
		str.erase(str.begin() + 0);
	}
	while (str[str.length() - 1] == ' ')
	{
		str.erase(str.begin() + str.length() - 1);
	}
	for (int i = 0; i < str.length(); i++)
	{
		if ((str[i] == ' ') && (str[i + 1] == ' ')) {
			str.erase(str.begin() + i);
			i--;
		}
	}
}
string RandomID(DS_SINH_VIEN ds_sv)
{
	string randomId = "MSSV00000000";
	char cloned[MAX_MASV];
	// max 12 ki tu, con lai chua ki tu ket thuc chuoi.
	strcpy_s(cloned, MAX_MASV, randomId.c_str());
	do
	{
		for (int i = 4; i < randomId.length(); i++)
		{
			randomId[i] = rand() % (57 - 48 + 1) + 48;
		}
	} while (CheckExistMSSV(ds_sv, cloned));
	return randomId;
}
string RandomIDMH(DS_MON_HOC ds_mon_hoc)
{
	string randomId = "MSMH000000";
	char cloned[MAX_MAMH];
	// max 11 ki tu, con lai chua ki tu ket thuc chuoi.
	strcpy_s(cloned, MAX_MAMH, randomId.c_str());
	do
	{
		for (int i = 4; i < randomId.length(); i++)
		{
			randomId[i] = rand() % (57 - 48 + 1) + 48;
		}
	} while (CheckExistMaMH(ds_mon_hoc, cloned));
	return randomId;
}
int RandomIDLTC(TREE tree) {
	int maLopTc;
	do
	{
		maLopTc = rand() % (999 - 100 + 1) + 100;
	} while (CheckExistMaLTC(tree, maLopTc));
	return maLopTc;
}
bool IsNumber(char* s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] <= 47) || (s[i] >= 58))
		{
			return false;
		}
		i++;
	}
	return true;
}
bool CheckExistLop(char* malop)
{
	ifstream fileIn;
	fileIn.open("DS_LOP.txt", ios_base::in);
	if (fileIn.fail())
	{
		cout << "Open file (DS_LOP.txt) failed. Please check and update path of file again !!!" << endl;
		return false;
	};
	bool exist = false;
	while (fileIn.peek() != EOF)
	{
		char temp[MAX_MALOP];
		fileIn.getline(temp, MAX_MALOP, ',');
		if (_strcmpi(temp, malop) == 0) {
			exist = true;
		}
	}
	fileIn.close();
	return exist;
}
void InsertLopIntoDSLop(string lop) {
	ofstream fileOut;
	fileOut.open("DS_LOP.txt", ios_base::app);
	if (fileOut.fail())
	{
		cout << "Open file (DS_LOP.txt) failed. Please check and update path of file again !!!" << endl;
	};
	fileOut << "," << lop;
	fileOut.close();
}
char** CreateArray(int x, int y) {
	char** a = new char* [y];
	for (int i = 0; i < y; i++)
	{
		a[i] = new char[x];
	}
	return a;
}
int countTotalSvByLop(DS_SINH_VIEN ds_sv, char* maLop) {
	int total = 0;
	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		if (_strcmpi(p->data.MALOP, maLop) == 0) {
			total++;
		}
	}
	return total;
}
SINH_VIEN** CreateArraySV(int x, int y) {
	SINH_VIEN** sv = new SINH_VIEN * [y];
	for (int i = 0; i < y; i++)
	{
		sv[i] = new SINH_VIEN[x];
	}
	return sv;
}
SV_DIEM** CreateArraySV_DIEM(int x, int y) {
	SV_DIEM** sv = new SV_DIEM * [y];
	for (int i = 0; i < y; i++)
	{
		sv[i] = new SV_DIEM[x];
	}
	return sv;
}
void ClearMessage(int x, int y, int length) {
	Sleep(1000);
	gotoXY(x, y);
	for (int i = 0; i < length; i++)
	{
		cout << " ";
	}
}

bool CheckInputBoxIsNull(string str[], int n) {
	int i = 0;
	bool exist = false;
	while (i < n)
	{
		if (str[i].length() == 0) {
			exist = true;
			break;
		}
		++i;
	}
	return exist;
}
void DrawEachButtonOfAction(MenuItem& item, int color = color_darkwhite) {
	SetColor(color);
	rectagle(item.rect.left, item.rect.top, item.rect.right, item.rect.bottom);
	gotoXY(item.rect.left + (item.rect.right - item.name.length()) / 2, item.rect.top + 1);
	cout << item.name;
}
void DrawListMenu(MenuContent& menucontent, int color = color_darkwhite) {
	for (int i = 0; i < menucontent.n; i++)
	{
		DrawEachButtonOfAction(menucontent.menus[i], color); // +3
	}
}
void HideCursor(bool isHide)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = !isHide;
	SetConsoleCursorInfo(consoleHandle, &info);
}
char InputBox(string& str, int x, int y, int width,
	int maxText, bool isDraw = false, bool isText = true, bool isPhone = false, bool isFloat = false) {
	string text = str;
	SetColor(color_darkwhite);
	rectagle(x, y, width, 2);


	char key = -1;
	gotoXY(x + 1, y + 1);
	cout << text;

	if (isDraw) return -1;

	HideCursor(false);

	do {
		key = inputKey();
		if (isPhone && key > 47 && key < 58 && text.length() < maxText) {
			text += key;
			cout << key;
		}
		else if (isText ?
			(((
				(key > 47 && key < 58) || (key > 64 && key < 91)
				|| (key > 96 && key < 123)) || key == 45 || key == 32)
				&& text.length() < maxText && key != key_Down
				&& key != key_Up && key != key_Right && key != key_Left)
			: ((key > 47 && key < 58) && text.length() < maxText)) {
			text += key;
			cout << key;
		}
		else if (isFloat && ((key > 47 && key < 58) || key == 46) && text.length() < maxText
			&& text.length() < maxText && key != key_Down
			&& key != key_Up && key != key_Right && key != key_Left
			) {
			text += key;
			cout << key;
		}
		else if (key == key_bkspace)
		{
			if (text.length() <= 0) continue;

			cout << "\b \b";
			text.erase(text.length() - 1, 1);
		}

	} while (key != key_esc && key != key_tab && key != key_Enter);

	HideCursor(true);
	str = text;
	return key;
}
char DrawFormInputSinhVien(int x, int y, int width, string Texts[], int maxText[], int n, bool isUpdate) {

	int offset = 3;

	for (int i = 0; i < n; i++)
	{
		// n - 1 => nam sinh
		if (n == 7) {
			gotoXY(50, y + (i * offset + 1));
			cout << propertySinhVien[i];
		}
		else if (n == 1) {
			gotoXY(45, y + (i * offset + 1));
			cout << "Nhap ma lop: ";
		}
		InputBox(Texts[i], x, y + (i * offset), width, maxText[i], true, i < n - 1 ? true : false);
	}

	int indexCurrent = isUpdate ? 1 : 0;
	int key = -1;

	do
	{
		key = InputBox(Texts[indexCurrent], x, y + (indexCurrent * offset),
			width, maxText[indexCurrent], false,
			((n == 7 && indexCurrent < n - 1 && indexCurrent != n - 2) || n == 1) ? true : false,
			(n == 7 && indexCurrent == n - 2) ? true : false);
		if (key == key_tab && n == 7) {
			if (indexCurrent == 6 && isUpdate) { indexCurrent = 1; }
			else indexCurrent = (indexCurrent + 1) % n;
		}
		else if (key == key_esc && n == 1) {
			return key;
		}
		else if (key == key_esc && isUpdate) return key;

	} while (key != key_Enter);
	return key;
}
void ConfirmDialog(string title) {
	rectagle(50, 5, 40, 13);
	gotoXY(58, 8);
	cout << title;
	DrawListMenu(ActionConfirm);
}

int ControlMenu(MenuContent* menuContent, int defaultColor = color_darkwhite, int activateColor = color_green) {
	int pos = menuContent->posStatus;
	int key = -1;
	DrawListMenu(*menuContent, defaultColor);
	DrawEachButtonOfAction(menuContent->menus[pos], activateColor);
	do
	{
		key = inputKey();
		switch (key)
		{
		case key_Up: {
			if (pos == 0) {
				pos = menuContent->n;
			}
			pos -= 1;
			goto paint;
		}
		case key_tab:
		case key_Down: {
			if (pos == menuContent->n - 1) {
				pos = -1;
			}
			pos += 1;
			goto paint;
		}
		default:
			break;
		paint: {
			DrawEachButtonOfAction(menuContent->menus[menuContent->posStatus], color_darkwhite);
			DrawEachButtonOfAction(menuContent->menus[pos], activateColor);
			menuContent->posStatus = pos;
			}
		}

	} while (key != key_esc && key != key_Enter);
	return key;
}
int ControlSinhVienDkyLTC(AppContext& context, int positionSubmenu) {
	int key = -1;
	key = Search_SV_Dky_LTCByConditions(context, positionSubmenu);
	if (key == key_esc) return key;
	return key;
}
// ===== END HELPER =====

// HANDLE FILES
void Read_File_MonHoc(DS_MON_HOC& ds_mon_hoc)
{
	fstream fileIn;
	fileIn.open("DS_MONHOC.txt", ios_base::in);
	if (fileIn.fail())
	{
		cout << "Open file (DS_MONHOC.txt) failed. Please check and update path of file again !!!" << endl;
		return;
	};
	while (fileIn.peek() != EOF)
	{
		MON_HOC* data = new MON_HOC;
		fileIn.getline(data->MAMH, MAX_MAMH, ',');
		fileIn.getline(data->TENMH, MAX_TENMH, ',');
		fileIn >> data->STCLT;
		fileIn.ignore(1);
		fileIn >> data->STCTH;
		fileIn.ignore(1);
		ds_mon_hoc.ds[ds_mon_hoc.n] = data;
		ds_mon_hoc.n++;
	}
	fileIn.close();
}
void UpdateFileDSMonHoc(DS_MON_HOC ds_mh) {
	ofstream fileOut;
	fileOut.open("DS_MONHOC.txt", ios_base::out);
	if (fileOut.fail())
	{
		cout << "Open file (DS_MONHOC.txt) failed. Please check and update path of file again !!!" << endl;
		return;
	};
	for (int i = 0; i < ds_mh.n; i++)
	{
		fileOut << ds_mh.ds[i]->MAMH << "," << ds_mh.ds[i]->TENMH
			<< "," << ds_mh.ds[i]->STCLT << "," << ds_mh.ds[i]->STCTH << endl;
	}
	fileOut.close();
}
void UpdateListStudentToFile(DS_SINH_VIEN& ds_sv) {
	ofstream fileOut;
	fileOut.open("DS_SINH_VIEN.txt", ios::out);
	if (fileOut.fail())
	{
		cout << "Open file (DS_SINH_VIEN.txt) to write failed. Please check and update path of file again !!!" << endl;
		return;
	};
	for (NODE_SINH_VIEN* sv = ds_sv.pHead; sv != NULL; sv = sv->pNext)
	{
		fileOut << sv->data.MALOP << "," << sv->data.MASV << "," << sv->data.HO << ","
			<< sv->data.TEN << "," << sv->data.PHAI << "," << sv->data.SDT << "," << sv->data.NAMNHAPHOC << endl;
	}
	fileOut.close();
}
void InsertLastSv(DS_SINH_VIEN& ds_sv, NODE_SINH_VIEN* nodeSV)
{
	if (ds_sv.pHead == NULL)
	{
		ds_sv.pHead = ds_sv.pTail = nodeSV;
		nodeSV->pNext = NULL;
	}
	else
	{
		ds_sv.pTail->pNext = nodeSV;
		ds_sv.pTail = nodeSV;
		nodeSV->pNext = NULL;
	}
	ds_sv.totalSv++;
}
void InsertFirstSv(DS_SINH_VIEN& ds_sv, NODE_SINH_VIEN* nodeSV)
{
	if (ds_sv.pHead == NULL)
	{
		ds_sv.pHead = ds_sv.pTail = nodeSV;
		nodeSV->pNext = NULL;
	}
	else
	{
		nodeSV->pNext = ds_sv.pHead;
		ds_sv.pHead = nodeSV;
	}
}
void InsertAndSortSvIntoDS(DS_SINH_VIEN& ds_sv, NODE_SINH_VIEN* nodeSV)
{
	if (ds_sv.pHead == NULL)
	{
		ds_sv.pHead = ds_sv.pTail = nodeSV;
		nodeSV->pNext = NULL;
	}
	else
	{
		ds_sv.pTail->pNext = nodeSV;
		NODE_SINH_VIEN* trav = ds_sv.pHead, * prev = NULL;

		int cmp = _strcmpi(trav->data.MALOP, nodeSV->data.MALOP);
		while (cmp < 0 || (cmp == 0 && _strcmpi(trav->data.MASV, nodeSV->data.MASV) < 0)) {
			prev = trav;
			trav = trav->pNext;
			cmp = _strcmpi(trav->data.MALOP, nodeSV->data.MALOP);
		}

		if (trav == nodeSV) {//het ds
			ds_sv.pTail = trav;
			trav->pNext = NULL;
		}
		else if (prev == NULL) {
			InsertFirstSv(ds_sv, nodeSV);
		}
		else {
			prev->pNext = nodeSV;
			nodeSV->pNext = trav;
		}
		ds_sv.pTail->pNext = NULL;
	}
	ds_sv.totalSv++;
}
void ReadFileSinhVien(DS_SINH_VIEN& ds_sv)
{
	ifstream fileIn;
	fileIn.open("DS_SINH_VIEN.txt", ios_base::in);
	if (fileIn.fail())
	{
		cout << "Open file (DS_SINH_VIEN.txt) failed. Please check and update path of file again !!!" << endl;
		return;
	};
	while (fileIn.peek() != EOF)
	{
		NODE_SINH_VIEN* node = new NODE_SINH_VIEN;
		fileIn.getline(node->data.MALOP, MAX_MALOP, ',');
		fileIn.getline(node->data.MASV, MAX_MASV, ',');
		fileIn.getline(node->data.HO, MAX_HO, ',');
		fileIn.getline(node->data.TEN, MAX_TEN, ',');
		fileIn.getline(node->data.PHAI, MAX_PHAI, ',');
		fileIn.getline(node->data.SDT, MAX_SDT, ',');
		fileIn >> node->data.NAMNHAPHOC;
		fileIn.ignore(1);
		node->pNext = NULL;
		InsertAndSortSvIntoDS(ds_sv, node);
	}
	fileIn.close();
}
NODE_SINH_VIEN* GetSinhVien(DS_SINH_VIEN ds_sv, char* masv) {
	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		if (_strcmpi(p->data.MASV, masv) == 0) return p;
	}
	return NULL;
}

// DANH SACH DANG KY
//void InsertLastDSDKY(DS_DANG_KY& ds_dk, DANG_KY* dk);
void ReadFileDS_DANG_KY(DS_SV_DANG_KY& ds_dk)
{
	ifstream fileIn;
	fileIn.open("DS_DANG_KY.txt", ios_base::in);
	if (fileIn.fail())
	{
		cout << "Open file (DS_DANG_KY.txt) failed. Please check and update path of file again !!!" << endl;
		return;
	};
	while (fileIn.peek() != EOF)
	{
		SV_DANG_KY* node = new SV_DANG_KY;
		fileIn.getline(node->MASV, MAX_MASV, ',');
		fileIn >> node->DIEM;
		fileIn.ignore();
		InsertLastDSDKY(ds_dk, node);
	}
	fileIn.close();
}

// END DANH SACH DANG KY

void UpdateListLopTinChiToFile(Lop_Tin_Chi* ds[], int n) {
	ofstream fileOut;
	fileOut.open("DS_LOP_TIN_CHI.txt", ios::out | ios::binary);
	if (fileOut.fail())
	{
		cout << "Open file (DS_LOP_TIN_CHI.txt) to write failed."
			<< "Please check and update path of file again !!!" << endl;
		return;
	};
	fileOut << n << endl;
	for (int i = 0; i < n; i++)
	{
		if (ds[i]->ds_sv_dky.pHead != NULL && ds[i]->totalSvDK != 0) {
			string masvDKLTC = "";
			for (SV_DANG_KY* p = ds[i]->ds_sv_dky.pHead; p != NULL; p = p->pNext) {
				std::ostringstream ss; // conver float to string
				ss << p->DIEM;
				masvDKLTC = masvDKLTC + "{" + (string)p->MASV + "," + ss.str() + "}";
				if (p->pNext != NULL) {
					masvDKLTC += ",";
				}
			}
			fileOut << ds[i]->MAMH << "," << ds[i]->NIEN_KHOA
				<< "," << ds[i]->MALOPTC << "," << ds[i]->HOC_KY << "," << ds[i]->NHOM << "," << ds[i]->sv_max << ","
				<< ds[i]->sv_min << "," << ds[i]->totalSvDK << ",[" << masvDKLTC << "]" << endl;
		}
		else {
			fileOut << ds[i]->MAMH << "," << ds[i]->NIEN_KHOA << ","
				<< ds[i]->MALOPTC << "," << ds[i]->HOC_KY << "," << ds[i]->NHOM << "," << ds[i]->sv_max
				<< "," << ds[i]->sv_min << "," << 0 << endl;
		}
	}

	fileOut.close();
}
void InsertNodeIntoTree(TREE& tree, Lop_Tin_Chi* data);
void ReadListLopTinChi(TREE& t, int& nLTC) {
	ifstream fileIn;
	fileIn.open("DS_LOP_TIN_CHI.txt", ios::in);
	if (fileIn.fail())
	{
		cout << "Open file (DS_LOP_TIN_CHI.txt) failed. Please check and update path of file again !!!" << endl;
		return;
	};

	fileIn >> nLTC;
	fileIn.ignore(1);
	while (fileIn.peek() != EOF)
	{
		Lop_Tin_Chi* data = new Lop_Tin_Chi;
		/*fileOut << endl << ds[i]->MALOPTC << "," << ds[i]->MAMH << ","
			<< ds[i]->NIEN_KHOA << "," << ds[i]->HOC_KY << "," << ds[i]->NHOM
			<< "," << ds[i]->sv_max << "," << ds[i]->sv_min
			<< ",[" << {MSV123,10}" << "," << "{MSV234,9}" << "]" << "\n";*/
		fileIn.getline(data->MAMH, MAX_MAMH, ',');
		fileIn.getline(data->NIEN_KHOA, MAX_NIENKHOA, ',');
		fileIn >> data->MALOPTC;
		fileIn.ignore(1);
		fileIn >> data->HOC_KY;
		fileIn.ignore(1);
		fileIn >> data->NHOM;
		fileIn.ignore(1);
		fileIn >> data->sv_max;
		fileIn.ignore(1);
		fileIn >> data->sv_min;
		fileIn.ignore(1);

		Init_DS_Dang_Ky(data->ds_sv_dky);
		fileIn >> data->totalSvDK;

		if (data->totalSvDK > 0) {
			fileIn.ignore(2);
			for (int i = 0; i < data->totalSvDK; i++)
			{
				SV_DANG_KY* p = new SV_DANG_KY;
				fileIn.ignore(1);
				fileIn.getline(p->MASV, MAX_MASV, ',');
				fileIn >> p->DIEM;
				fileIn.ignore(2);
				InsertLastDSDKY(data->ds_sv_dky, p);
			}
		}
		fileIn.ignore(1);
		InsertNodeIntoTree(t, data);
	}
	fileIn.close();
}
// END HANDLE FILES

// SINH VIEN
void Init_DS_Sinh_Vien(DS_SINH_VIEN& ds)
{
	ds.pHead = NULL;
	ds.pTail = NULL;
	ds.totalSv = 0;
}
bool isEmptyDSSV(DS_SINH_VIEN ds_sv)
{
	if (ds_sv.pHead == NULL && ds_sv.pTail == NULL)
		return true;
	return false;
}
void RemoveFirst(DS_SINH_VIEN& ds_sv)
{
	NODE_SINH_VIEN* p;
	if (ds_sv.pHead == NULL)
		return;

	p = ds_sv.pHead;
	ds_sv.pHead = p->pNext;
	ds_sv.totalSv--;
	delete p;
}
void RemoveLast(DS_SINH_VIEN& ds_sv)
{
	if (ds_sv.pHead == NULL)
		return;

	if (ds_sv.pHead->pNext == NULL)
	{
		RemoveFirst(ds_sv);
		return;
	}
	for (NODE_SINH_VIEN* k = ds_sv.pHead; k != NULL; k = k->pNext)
	{
		if (k->pNext == ds_sv.pTail)
		{
			delete ds_sv.pTail;
			k->pNext = NULL;
			ds_sv.pTail = k;
			ds_sv.totalSv--;
			return;
		}
	}
}
void RemoveSvByMSSV(DS_SINH_VIEN& ds_sv, char* massv)
{
	if (isEmptyDSSV(ds_sv))
	{
		cout << "Danh sach dang rong. Khong the thuc hien chuc nang nay!" << endl;
		return;
	}
	if (_strcmpi(ds_sv.pHead->data.MASV, massv) == 0)
	{
		RemoveFirst(ds_sv);
		return;
	}
	if (_strcmpi(ds_sv.pTail->data.MASV, massv) == 0)
	{
		RemoveLast(ds_sv);
		return;
	}
	NODE_SINH_VIEN* g = new NODE_SINH_VIEN;
	for (NODE_SINH_VIEN* k = ds_sv.pHead; k != NULL; k = k->pNext)
	{
		if (_strcmpi(k->data.MASV, massv) == 0)
		{
			g->pNext = k->pNext;
			delete k;
			ds_sv.totalSv--;
			return;
		}
		g = k;
	}
}
NODE_SINH_VIEN* Input_Sinh_Vien(DS_SINH_VIEN ds_sv)
{
	int slsv;
	NODE_SINH_VIEN* sv = new NODE_SINH_VIEN;
	cout << "\nNhap ma lop: ";
	cin.getline(sv->data.MALOP, MAX_MALOP);
	if (sv == NULL)
	{
		cout << "Cap phat vung nho de khoi tao sv that bai." << endl;
		system("pause");
		return NULL;
	}
	cout << "\nNhap ho: ";
	cin.getline(sv->data.HO, MAX_HO);
	cout << "\nNhap ten: ";
	cin.getline(sv->data.TEN, MAX_TEN);
	cout << "\nNhap gioi tinh: ";
	cin.getline(sv->data.PHAI, MAX_PHAI);
	do
	{
		cout << "\nNhap so dien thoai: ";
		cin.getline(sv->data.SDT, MAX_SDT);
		if (!IsNumber(sv->data.SDT)) {
			cout << "Phone number invalid !";
			Sleep(2000);
			system("cls");
		}
	} while (!IsNumber(sv->data.SDT));
	cout << "\nNhap nam hoc: ";
	cin >> sv->data.NAMNHAPHOC;
	strcpy_s(sv->data.MASV, MAX_MASV, RandomID(ds_sv).c_str());
	sv->pNext = NULL;
	return sv;
}
void UpdateSinhVien(DS_SINH_VIEN& ds_sv, SINH_VIEN* sv) {

	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		if (_strcmpi(p->data.MASV, sv->MASV) == 0) {
			p->data = *sv;
			break;
		}
	}
}
void SortSinhVienByMSSV(SINH_VIEN* sv[], int n) {
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (_strcmpi(sv[i]->MASV, sv[j]->MASV) > 0) {
				SINH_VIEN* temp;
				temp = sv[i];
				sv[i] = sv[j];
				sv[j] = temp;
			}
		}
	}
}
void Show_DS_Sinh_Vien(DS_SINH_VIEN ds_sv)
{
	int total = 0;
	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		cout << "========== SINH VIEN " << ++total << " ==========" << endl;
		cout << "Ma lop: " << p->data.MALOP << endl;
		cout << "Ma SV: " << p->data.MASV << endl;
		cout << "Nam nhap hoc: " << p->data.NAMNHAPHOC << endl;
		cout << "Phai: " << p->data.PHAI << endl;
		cout << "So dien thoai: " << p->data.SDT << endl;
		cout << "Ho ten: " << p->data.HO << " " << p->data.TEN << endl;
	}
}
//  END SINH VIEN

// ===== BEGIN DS LOP TIN CHI =====
void InitTree(TREE& tree) {
	tree = NULL;
}
void InsertNodeIntoTree(TREE& tree, Lop_Tin_Chi* data) {
	if (tree == NULL) {
		NODE_LOP_TIN_CHI* p = new NODE_LOP_TIN_CHI;
		p->data.ds_sv_dky = data->ds_sv_dky;
		p->data.HOC_KY = data->HOC_KY;
		p->data.MALOPTC = data->MALOPTC;
		strcpy_s(p->data.MAMH, MAX_MAMH, data->MAMH);
		p->data.NHOM = data->NHOM;
		strcpy_s(p->data.NIEN_KHOA, MAX_NIENKHOA, data->NIEN_KHOA);
		p->data.sv_max = data->sv_max;
		p->data.sv_min = data->sv_min;
		p->data.totalSvDK = data->totalSvDK;
		p->pLeft = NULL;
		p->pRight = NULL;
		tree = p;
	}
	else {
		if (tree->data.MALOPTC > data->MALOPTC) {
			InsertNodeIntoTree(tree->pLeft, data);
		}
		else if (tree->data.MALOPTC < data->MALOPTC) {
			InsertNodeIntoTree(tree->pRight, data);
		}
	}
}
NODE_LOP_TIN_CHI* TravelTree(TREE t, int maLop) {
	if (t == NULL) return NULL;
	if (t->data.MALOPTC > maLop) {
		TravelTree(t->pLeft, maLop);
	}
	else if (t->data.MALOPTC < maLop) {
		TravelTree(t->pRight, maLop);
	}
	else {
		return t;
	}
}
void InsertLopTCIntoTree(TREE& tree) {
	Lop_Tin_Chi* p = new Lop_Tin_Chi;
	p->MALOPTC = RandomIDLTC(tree);
	cout << "\nNhap ma mon hoc: "; cin.getline(p->MAMH, MAX_MAMH);
	cout << "Nhap nien khoa: "; cin.getline(p->NIEN_KHOA, MAX_NIENKHOA);
	cout << "Nhap hoc ky: "; cin >> p->HOC_KY;
	cout << "Nhap sl sinh vien max: "; cin >> p->sv_max;
	cout << "Nhap sl sinh vien min: "; cin >> p->sv_min;
	cout << "Nhap nhom:"; cin >> p->NHOM;
	p->ds_sv_dky.pHead = NULL;
	p->ds_sv_dky.pTail = NULL;
	InsertNodeIntoTree(tree, p);
}
void ConvertTreeToArray(TREE t, Lop_Tin_Chi* ds[], int& n) {
	if (t != NULL) {
		ConvertTreeToArray(t->pLeft, ds, n);
		ds[n] = new Lop_Tin_Chi;
		ds[n] = &t->data;
		n++;
		ConvertTreeToArray(t->pRight, ds, n);
	}
}
void ConvertLinkedListSV(DS_SINH_VIEN ds_sv, SINH_VIEN* dsSV[]) {
	int i = 0;
	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		dsSV[i] = &p->data;
		i++;
	}
}
void ConvertLinkedListSVBylop(DS_SINH_VIEN ds_sv, SINH_VIEN* dsSV[], char* maLop) {
	int i = 0;
	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		if (_strcmpi(p->data.MALOP, maLop) == 0) {
			dsSV[i] = &p->data;
			i++;
		}
	}
}
void Node_The_Mang(TREE& t, TREE& x) {
	if (t->pLeft != NULL) {
		Node_The_Mang(t->pLeft, x);
	}
	else {
		t->data = x->data;
		t = x;
		x = x->pRight;
	}
}
void RemoveNodeOfTree(TREE& t, int ma, int& nLTC) {
	if (t == NULL) return;
	if (t->data.MALOPTC > ma) {
		RemoveNodeOfTree(t->pLeft, ma, nLTC);
	}
	else if (t->data.MALOPTC < ma) {
		RemoveNodeOfTree(t->pRight, ma, nLTC);
	}
	else {
		NODE_LOP_TIN_CHI* p = t;
		if (t->pLeft == NULL) {
			t = t->pRight;
		}
		else if (t->pRight == NULL) {
			t = t->pLeft;
		}
		else {
			// trai nhat cay con phai
			Node_The_Mang(t->pRight, p);
		}
		delete p;
	}
}
void UpdateNodeOfTree(TREE& t, Lop_Tin_Chi* data) {
	if (t != NULL) {
		if (t->data.MALOPTC == data->MALOPTC) {
			strcpy_s(t->data.MAMH, data->MAMH);
			t->data.NHOM = data->NHOM;
			strcpy_s(t->data.NIEN_KHOA, data->NIEN_KHOA);
			t->data.HOC_KY = data->HOC_KY;
			t->data.sv_max = data->sv_max;
			t->data.sv_min = data->sv_min;
		}
		else {
			if (t->data.MALOPTC > data->MALOPTC) {
				UpdateNodeOfTree(t->pLeft, data);
			}
			if (t->data.MALOPTC < data->MALOPTC) {
				UpdateNodeOfTree(t->pRight, data);
			}
		}
	}

}
Lop_Tin_Chi* InputUpdateTree() {
	Lop_Tin_Chi* p = new Lop_Tin_Chi;
	cout << "\nNhap ma lop tc:"; cin >> p->MALOPTC; // ma lop tc can update
	cin.ignore();
	cout << "\nNhap ma mon hoc: "; cin.getline(p->MAMH, MAX_MAMH);
	cout << "Nhap nien khoa: "; cin.getline(p->NIEN_KHOA, MAX_NIENKHOA);
	cout << "Nhap hoc ky: "; cin >> p->HOC_KY;
	cout << "Nhap sl sinh vien max: "; cin >> p->sv_max;
	cout << "Nhap sl sinh vien min: "; cin >> p->sv_min;
	cout << "Nhap nhom:"; cin >> p->NHOM;
	// p->ds_sv = NULL; TODO:
	return p;
}
bool CheckLopTinChiToInsert(Lop_Tin_Chi* ds[], int n, Lop_Tin_Chi* data) {
	int i = 0;
	while (i < n)
	{
		if (_strcmpi(ds[i]->MAMH, data->MAMH) == 0
			&& _strcmpi(ds[i]->NIEN_KHOA, data->NIEN_KHOA) == 0
			&& ds[i]->HOC_KY == data->HOC_KY && ds[i]->NHOM == data->NHOM) {
			return true;
		}
		++i;
	}
	return false;
}
bool CheckLopTinChiToUpdate(Lop_Tin_Chi* ds[], int n, Lop_Tin_Chi* data) {
	int i = 0;
	while (i < n)
	{
		if (ds[i]->MALOPTC == data->MALOPTC) {
			i++;
			continue;
		}
		if (_strcmpi(ds[i]->MAMH, data->MAMH) == 0
			&& _strcmpi(ds[i]->NIEN_KHOA, data->NIEN_KHOA) == 0
			&& ds[i]->HOC_KY == data->HOC_KY && ds[i]->NHOM == data->NHOM) {
			return true;
		}
		++i;
	}
	return false;
}
char DrawFormInputLTC(int x, int y, int width, string Texts[], int maxText[], int n, bool isUpdate) {

	int offset = 3;

	for (int i = 0; i < n; i++)
	{
		// show to update
		if (n == 7) {
			gotoXY(50, y + (i * offset + 1));
			cout << propertyLopTinChi[i];
		}
		else if (n == 4)// In ds sv theo dieu kien Lop tin chi 
		{
			gotoXY(50, y + (i * offset + 1));
			cout << propertyLopTinChiByConditions[i];
		}
		else if (n == 6) { // show to insert
			gotoXY(50, y + (i * offset + 1));
			cout << propertyInsertLopTinChi[i];
		}
		InputBox(Texts[i], x, y + (i * offset), width, maxText[i], true, i < n - 1 ? true : false);
	}

	int indexCurrent = isUpdate ? 1 : 0;
	int key = -1;
	do
	{
		bool isText = ((n == 7 && indexCurrent < 3) || ((n == 4 || n == 6) && indexCurrent < 2)) ? true : false;
		key = InputBox(Texts[indexCurrent], x, y + (indexCurrent * offset),
			width, maxText[indexCurrent], false, isText, false);
		if (key == key_tab && n == 7) {
			if (indexCurrent == 6 && isUpdate) { indexCurrent = 1; }
			else indexCurrent = (indexCurrent + 1) % n;
		}
		else if (key == key_tab && n == 6) {
			indexCurrent = (indexCurrent + 1) % n;
		}
		else if (key == key_esc) return key;
		/*else if (key == key_esc && n == 1) {
			return key;
		}*/
		//else if (key == key_esc && isUpdate) return key;

	} while (key != key_Enter);
	return key;
}
char DrawFormInputSearchLTC(int x, int y, int width, string Texts[], int maxText[], int n, bool isStudent) {

	int offset = 3;

	for (int i = 0; i < n; i++)
	{
		gotoXY(50, y + (i * offset + 1));
		// giang vien => 4 form, sinh vien search-dang ky lop => 2 form input
		if (isStudent) {
			cout << propertySVDangKyLopTinChiByConditions[i];
		}
		else {
			cout << propertyLopTinChiByConditions[i];
		}
		InputBox(Texts[i], x, y + (i * offset), width, maxText[i], true, i < n - 1 ? true : false);
	}

	int indexCurrent = 0;
	int key = -1;

	do
	{
		key = InputBox(Texts[indexCurrent], x, y + (indexCurrent * offset),
			width, maxText[indexCurrent], false,
			(!isStudent ? indexCurrent < 2 : indexCurrent < 1) ? true : false, false, false);
		// <2 => ma mon hoc, nien khoa =) text
		// <1 sinh vien search de dky (1-nien khoa, 2 hoc ky)
		if (key == key_tab) {
			indexCurrent = (indexCurrent + 1) % n;
		}
		else if (key == key_esc) {
			return key;
		}
	} while (key != key_Enter);
	return key;
}
Lop_Tin_Chi** CreateArrayLopTinChi(int x, int y) {
	Lop_Tin_Chi** ltc = new Lop_Tin_Chi * [y];
	for (int i = 0; i < y; i++)
	{
		ltc[i] = new Lop_Tin_Chi[x];
	}
	return ltc;
}
int total_LTC_SV_Can_Register(Lop_Tin_Chi* ltc[], int n, char* nienkhoa, int hoc_ky) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (_strcmpi(ltc[i]->NIEN_KHOA, nienkhoa) == 0
			&& ltc[i]->HOC_KY == hoc_ky) {
			count++;
		}
	}
	return count;
}
int total_LTC_SV_Registered(Lop_Tin_Chi* ltc[], int n, char* masv) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (SV_DANG_KY* p = ltc[i]->ds_sv_dky.pHead; p != NULL; p = p->pNext)
		{
			if ((_strcmpi(p->MASV, masv) == 0)) {
				count++;
			}
		}
	}
	return count;
}
Lop_Tin_Chi** FindLTCSVDKYByConditions(Lop_Tin_Chi* ltc[], int n, int& total, char* nienkhoa, int hoc_ky) {
	int result = total_LTC_SV_Can_Register(ltc, n, nienkhoa, hoc_ky);
	if (result == 0) return NULL;
	Lop_Tin_Chi** ltcSvDky = CreateArrayLopTinChi(result, sizeof(Lop_Tin_Chi));
	for (int i = 0; i < n; i++) {
		if (_strcmpi(ltc[i]->NIEN_KHOA, nienkhoa) == 0
			&& ltc[i]->HOC_KY == hoc_ky) {
			ltcSvDky[total] = ltc[i];
			total++;
		}
	}
	return ltcSvDky;
}
Lop_Tin_Chi** TimLopTinChiSinhVienDaDangKy(Lop_Tin_Chi* ltc[], int n, int& total, char* masv) {
	int result = total_LTC_SV_Registered(ltc, n, masv);
	if (result == 0) return NULL;
	Lop_Tin_Chi** ltcSvDky = CreateArrayLopTinChi(result, sizeof(Lop_Tin_Chi));
	for (int i = 0; i < n; i++) {
		for (SV_DANG_KY* p = ltc[i]->ds_sv_dky.pHead; p != NULL; p = p->pNext)
		{
			if ((_strcmpi(p->MASV, masv) == 0)) {
				ltcSvDky[total] = ltc[i];
				total++;
			}
		}
	}
	return ltcSvDky;
}

template<class _T>
_T* CloneObject(_T* obj) {
	_T* t = new _T;
	*t = *obj;
	return t;
}

Lop_Tin_Chi* FindLTCByConditions(Lop_Tin_Chi* ltc[], int n, Search_SV_DK_LTC conditions) {
	for (int i = 0; i < n; i++)
	{
		if (_strcmpi(ltc[i]->MAMH, conditions.ma_mon_hoc) == 0
			&& _strcmpi(ltc[i]->NIEN_KHOA, conditions.nien_khoa) == 0
			&& ltc[i]->HOC_KY == conditions.hoc_ky && ltc[i]->NHOM == conditions.nhom
			) {
			return ltc[i];
		}
	}
	return NULL;
}
int Search_GV_LTCByConditions(AppContext& context, int positionSubmenu, bool isScoreFeature) {
	Search_SV_DK_LTC conditions;
	string Texts[4] = { "" };
	int maxTexts[4] = { MAX_MAMH - 1, MAX_NIENKHOA - 1,3,3 };

	SetColor(color_white | colorbk_green);
	rectagle(45, 4, 65, 15);
	SetColor(color_white);
	bool valid = true;
	int key = -1;
	do
	{
		key = DrawFormInputSearchLTC(70, 5, 30, Texts, maxTexts, 4, false);
		if (key == key_Enter) {
			if (!CheckInputBoxIsNull(Texts, 4)) {
				strcpy_s(conditions.ma_mon_hoc, MAX_MAMH, Texts[0].c_str());
				strcpy_s(conditions.nien_khoa, MAX_NIENKHOA, Texts[1].c_str());
				conditions.hoc_ky = atoi(Texts[2].c_str());
				conditions.nhom = atoi(Texts[3].c_str());
				context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
				context.nLTC = 0;
				ConvertTreeToArray(context.tree, context.ds, context.nLTC);
				Lop_Tin_Chi* single = FindLTCByConditions(context.ds, context.nLTC, conditions);
				// Lop_Tin_Chi* singleCloned = CloneObject(single);
				if (single != NULL) {
					DS_SINH_VIEN ds_sv_dky;
					Init_DS_Sinh_Vien(ds_sv_dky);

					for (SV_DANG_KY* p = single->ds_sv_dky.pHead; p != NULL; p = p->pNext)
					{
						NODE_SINH_VIEN* temp = GetSinhVien(context.ds_sv, p->MASV);
						NODE_SINH_VIEN* cloned = CloneObject(temp);

						if (cloned != NULL) {
							cloned->pNext = NULL;
							InsertAndSortSvIntoDS(ds_sv_dky, cloned);
						}
					}
					if (ds_sv_dky.totalSv == 0) {
						gotoXY(60, 18);
						cout << "Lop chua co sinh vien dang ky!";
						Sleep(1200);
						clrscr(40, 4, 90, 35, ' ');
						return -1;
					}
					clrscr(40, 4, 90, 35, ' ');
					if (ds_sv_dky.totalSv != 0 && !isScoreFeature) {
						key = CommonShowSvList(ds_sv_dky, positionSubmenu, NULL);
						if (key == key_esc) {
							/*delete singleCloned;
							delete[]context.ds;*/
							break;
						}
					}
					else if (ds_sv_dky.totalSv != 0 && isScoreFeature) {
						// TODO: Display / Update score of students
						SV_DIEM** ds_sv_diem = CreateArraySV_DIEM(ds_sv_dky.totalSv, sizeof(SV_DIEM));
						int idx = 0;
						for (SV_DANG_KY* p = single->ds_sv_dky.pHead; p != NULL; p = p->pNext) {
							NODE_SINH_VIEN* sv_tmp = GetSinhVien(context.ds_sv, p->MASV);
							if (sv_tmp != NULL) {
								strcpy_s(ds_sv_diem[idx]->masv, MAX_MASV, sv_tmp->data.MASV);
								strcpy_s(ds_sv_diem[idx]->ho, MAX_HO, sv_tmp->data.HO);
								strcpy_s(ds_sv_diem[idx]->ten, MAX_TEN, sv_tmp->data.TEN);
								ds_sv_diem[idx]->diem = p->DIEM;
								idx++;
							}
						}
						do
						{
							key = InDanhSachSinhVien_Diem(ds_sv_diem, idx, 45, 10);
							if (key == key_Enter) {
								// TODO: update score to ltc
								for (SV_DANG_KY* p = single->ds_sv_dky.pHead; p != NULL; p = p->pNext) {
									for (int i = 0; i < idx; i++) {
										if (_strcmpi(p->MASV, ds_sv_diem[i]->masv) == 0) {
											p->DIEM = ds_sv_diem[i]->diem;
											break;
										}
									}
								}
								UpdateNodeOfTree(context.tree, single);
								context.nLTC = 0;
								ConvertTreeToArray(context.tree, context.ds, context.nLTC);
								UpdateListLopTinChiToFile(context.ds, context.nLTC);
							}
						} while (key != key_esc);
						if (key == key_esc) {
							// TODO: Add confirm to quit form
							break;
						}
					}
				}
				else {
					gotoXY(60, 18);
					cout << "Khong tim thay du lieu!";
					Sleep(1500);
					delete single;
					valid = false;
				}
			}
			else {
				gotoXY(60, 18);
				cout << "Du lieu nhap khong duoc de trong!";
				Sleep(1500);
				valid = false;
			}
		}
		else if (key == key_esc) {
			clrscr(40, 4, 90, 35, ' ');
			break;
		}
	} while (!valid);
	return key;
}
int Search_SV_Dky_LTCByConditions(AppContext& context, int positionSubmenu) {
	// Danh sách lớp tín chỉ thõa mãn => Sinh viên đăng ký lớp tín chỉ !
	string Texts[2] = { "" };
	int maxTexts[2] = { MAX_NIENKHOA - 1, 3 };
	char nien_khoa[MAX_NIENKHOA];
	int hoc_ky;
	SetColor(color_white | colorbk_green);
	rectagle(45, 4, 65, 10);
	SetColor(color_white);
	bool valid = true;
	int key = -1;
	do
	{
		key = DrawFormInputSearchLTC(70, 5, 30, Texts, maxTexts, 2, true);
		if (key == key_Enter) {
			if (!CheckInputBoxIsNull(Texts, 2)) {
				strcpy_s(nien_khoa, MAX_NIENKHOA, Texts[0].c_str());
				hoc_ky = atoi(Texts[1].c_str());
				context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
				context.nLTC = 0;
				int total = 0;
				// TODO: lỗi khi in ds sv đăng ký ltc, sau đó quay lại in ds lớp tín chỉ để sv đki
				ConvertTreeToArray(context.tree, context.ds, context.nLTC);
				Lop_Tin_Chi** arrayLTC = FindLTCSVDKYByConditions(context.ds, context.nLTC, total, nien_khoa, hoc_ky);
				if (arrayLTC != NULL) {
					clrscr(40, 4, 100, 30, ' ');
					do
					{
						gotoXY(55, 3);
						SetColor(color_darkwhite);
						cout << "============ DANH SACH LOP TIN CHI DANG KY ============";
						key = InDanhSachLopTinChi(context, arrayLTC, total, 40, 5, positionSubmenu, true, true);
						// TODO: catch key tab => move pointer down list ltc sv registed
						if (key == key_tab || key == key_F1) {
							gotoXY(53, 23);
							SetColor(color_darkwhite);
							cout << "============ DANH SACH LOP TIN CHI DA DANG KY ============";
							do
							{
								// END
								int totalRegitered = 0;
								context.nLTC = 0;
								ConvertTreeToArray(context.tree, context.ds, context.nLTC);
								// TODO: Need to check remove ltc
								Lop_Tin_Chi** arrayLTCRegistered = TimLopTinChiSinhVienDaDangKy(
									context.ds, context.nLTC,
									totalRegitered, context.currentUser);
								key = InDanhSachLopTinChi(context, arrayLTCRegistered, totalRegitered, 40, 25, positionSubmenu, true, false);
							} while (key != key_tab);
						}
						if (key == key_esc) {
							clrscr(40, 3, 100, 35, ' ');
							delete[] arrayLTC;
							delete[] context.ds;
							return key;
						}
					} while (key != key_esc);
				}
				else {
					gotoXY(63, 13);
					cout << "Khong tim thay du lieu!";
					Sleep(1500);
					valid = false;
				}
			}
			else {
				gotoXY(63, 13);
				cout << "Du lieu nhap khong duoc de trong!";
				Sleep(1500);
				valid = false;
			}
		}
		else if (key == key_esc) {
			clrscr(40, 4, 90, 35, ' ');
			return key;
		}
	} while (!valid);
}
bool CheckSvExistLTC(Lop_Tin_Chi* ltc, char* masv) {
	for (SV_DANG_KY* p = ltc->ds_sv_dky.pHead; p != NULL; p = p->pNext)
	{
		if ((_strcmpi(p->MASV, masv) == 0)) {
			return true;
		}
	}
	return false;
}
// ===== END DS LOP TIN CHI =====

// MON HOC
void Insert_MonHoc(DS_MON_HOC& ds_mon_hoc)
{
	MON_HOC* monhoc = new MON_HOC;
	strcpy_s(monhoc->MAMH, MAX_MAMH, RandomIDMH(ds_mon_hoc).c_str());
	cout << "\nNhap vao ten mon hoc:";
	cin.getline(monhoc->TENMH, MAX_TENMH);
	if (strcmp(monhoc->TENMH, "") == 0)
	{
		cout << "\nLoi. Ten mon hoc khong hop le." << endl;
		system("pause");
	}
	cout << "\nNhap vao so tin chi ly thuyet:";
	cin >> monhoc->STCLT;

	cout << "\nNhap vao so tin chi thuc hanh:";
	cin >> monhoc->STCTH;
	cin.ignore();
	ds_mon_hoc.ds[ds_mon_hoc.n] = monhoc;
	ds_mon_hoc.n++;
}
void RemoveMonHoc(DS_MON_HOC& ds_mon_hoc, char* maMH)
{
	if (ds_mon_hoc.n == 0)
	{
		cout << "\nDanh sach mon hoc rong. Khong the thuc hien chuc nang nay!!!" << endl;
		return;
	}
	for (int i = 0; i < ds_mon_hoc.n; i++)
	{
		if (_strcmpi(ds_mon_hoc.ds[i]->MAMH, maMH) == 0)
		{
			for (int j = i; j < (ds_mon_hoc.n - 1); j++)
			{
				ds_mon_hoc.ds[j] = ds_mon_hoc.ds[j + 1];
			}
		}
	}
	ds_mon_hoc.n--;
}
void Show_DS_MonHoc(DS_MON_HOC dsMonHoc)
{
	for (int i = 0; i < dsMonHoc.n; i++)
	{
		cout << "Ma mon hoc: " << dsMonHoc.ds[i]->MAMH << endl;
		cout << "Ten mon hoc: " << dsMonHoc.ds[i]->TENMH << endl;
		cout << "So tin chi ly thuyet: " << dsMonHoc.ds[i]->STCLT << endl;
		cout << "So tin chi thuc hanh: " << dsMonHoc.ds[i]->STCTH << endl;
	}
}
char DrawFormInputMonHoc(int x, int y, int width, string Texts[], int maxText[], int n, bool isUpdate) {

	int offset = 3;

	for (int i = 0; i < n; i++)
	{
		gotoXY(50, y + (i * offset + 1));
		cout << propertyMonHoc[i];
		InputBox(Texts[i], x, y + (i * offset), width,
			maxText[i], true, i < 2 ? true : false, false, i>1 ? true : false);
	}

	int indexCurrent = isUpdate ? 1 : 0;
	int key = -1;

	do
	{
		key = InputBox(Texts[indexCurrent], x, y + (indexCurrent * offset),
			width, maxText[indexCurrent], false,
			indexCurrent < 2 ? true : false, false, indexCurrent>1 ? true : false);
		if (key == key_tab) {
			if (indexCurrent == 3 && isUpdate) { indexCurrent = 1; }
			else indexCurrent = (indexCurrent + 1) % n;
		}
		else if (key == key_esc && isUpdate) return key;

	} while (key != key_Enter);
	return key;
}
void UpdateMonHoc(DS_MON_HOC& ds_mon_hoc, MON_HOC* mh) {
	for (int i = 0; i < ds_mon_hoc.n; i++)
	{
		if (_strcmpi(ds_mon_hoc.ds[i]->MAMH, mh->MAMH) == 0) {
			strcpy_s(ds_mon_hoc.ds[i]->TENMH, MAX_TENMH, mh->TENMH);
			ds_mon_hoc.ds[i]->STCLT = mh->STCLT;
			ds_mon_hoc.ds[i]->STCTH = mh->STCTH;
			break;
		}
	}
}
void SortMonHocMyNameMH(DS_MON_HOC& ds_mh) {
	for (int i = 0; i < ds_mh.n - 1; i++)
	{
		for (int j = i + 1; j < ds_mh.n; j++)
		{
			if (_strcmpi(ds_mh.ds[i]->TENMH, ds_mh.ds[j]->TENMH) > 0) {
				MON_HOC* temp;
				temp = ds_mh.ds[i];
				ds_mh.ds[i] = ds_mh.ds[j];
				ds_mh.ds[j] = temp;
			}
		}
	}
}

// END MON HOC

// BEGIN DS SINH VIEN DANG KY
void Init_DS_Dang_Ky(DS_SV_DANG_KY& ds_dk)
{
	ds_dk.pHead = NULL;
	ds_dk.pTail = NULL;
}
void InsertLastDSDKY(DS_SV_DANG_KY& ds_dk, SV_DANG_KY* dk)
{
	if (ds_dk.pHead == NULL)
	{
		ds_dk.pHead = ds_dk.pTail = dk;
		dk->pNext = NULL;
	}
	else
	{
		ds_dk.pTail->pNext = dk;
		ds_dk.pTail = dk;
		dk->pNext = NULL;
	}
}
void Show_DS_Dang_Ky(DS_SV_DANG_KY ds_dk) {
	for (SV_DANG_KY* p = ds_dk.pHead; p != NULL; p = p->pNext) {
		cout << "Ma sv:" << p->MASV << endl;
		cout << "Diem:" << p->DIEM << endl;
	}
}
bool isEmptyDS_Dang_Ky(DS_SV_DANG_KY ds_dk)
{
	if (ds_dk.pHead == NULL && ds_dk.pTail == NULL)
		return true;
	return false;
}
void Remove_SV_Dang_Dky_First(DS_SV_DANG_KY& ds_dk)
{
	SV_DANG_KY* p;
	if (ds_dk.pHead == NULL)
		return;

	p = ds_dk.pHead;
	ds_dk.pHead = p->pNext;
	delete p;
}
void Remove_SV_Dang_Dky_Last(DS_SV_DANG_KY& ds_dk)
{
	if (ds_dk.pHead == NULL)
		return;

	if (ds_dk.pHead->pNext == NULL)
	{
		Remove_SV_Dang_Dky_First(ds_dk);
		return;
	}
	for (SV_DANG_KY* k = ds_dk.pHead; k != NULL; k = k->pNext)
	{
		if (k->pNext == ds_dk.pTail)
		{
			delete ds_dk.pTail;
			k->pNext = NULL;
			ds_dk.pTail = k;
			return;
		}
	}
}
int RemoveSV_Dang_Ky_ByMSSV(DS_SV_DANG_KY& ds_sv_dky, char* massv)
{
	if (isEmptyDS_Dang_Ky(ds_sv_dky))
	{
		return -1;
	}
	if (_strcmpi(ds_sv_dky.pHead->MASV, massv) == 0)
	{
		Remove_SV_Dang_Dky_First(ds_sv_dky);
		return 1;
	}
	if (_strcmpi(ds_sv_dky.pTail->MASV, massv) == 0)
	{
		Remove_SV_Dang_Dky_Last(ds_sv_dky);
		return 1;
	}
	SV_DANG_KY* g = new SV_DANG_KY;
	for (SV_DANG_KY* k = ds_sv_dky.pHead; k != NULL; k = k->pNext)
	{
		if (_strcmpi(k->MASV, massv) == 0)
		{
			g->pNext = k->pNext;
			delete k;
			return 1;
		}
		g = k;
	}
}
bool CheckSvHasScore(DS_SV_DANG_KY& ds_sv_dky, char* massv) {
	for (SV_DANG_KY* p = ds_sv_dky.pHead; p != NULL; p = p->pNext) {
		if (_strcmpi(p->MASV, massv) == 0) {
			if (p->DIEM != -1) return true;
		}
	}
	return false;
}

// END DS SINH VIEN DANG KY

void ShowSingleLTC(Lop_Tin_Chi* ltc, int index) {
	cout << setw(3) << index + 1 << char(179) << setw(10) << ltc->MALOPTC << char(179)
		<< setw(11) << ltc->MAMH << char(179)
		<< setw(6) << ltc->HOC_KY << char(179) << setw(4) << ltc->NHOM << char(179)
		<< setw(20) << ltc->NIEN_KHOA << char(179)
		<< setw(7) << ltc->sv_max << char(179)
		<< setw(7) << ltc->sv_min << char(179)
		<< setw(7) << ltc->sv_max - ltc->totalSvDK << char(179);
}
void ShowSingleSV(SINH_VIEN* sv, int index) {
	cout << setw(3) << index + 1 << char(179) << setw(15) << sv->MALOP << char(179)
		<< setw(13) << sv->MASV << char(179)
		<< setw(20) << sv->HO << char(179) << setw(15) << sv->TEN << char(179)
		<< setw(5) << sv->PHAI << char(179) << setw(11) << sv->SDT << char(179);
}
void ShowSingleSV_Diem(SV_DIEM* sv_diem, int index) {
	cout << setw(3) << index + 1 << char(179) << setw(15) << sv_diem->masv << char(179)
		<< setw(20) << sv_diem->ho << char(179) << setw(15) << sv_diem->ten << char(179)
		<< setw(5) << sv_diem->diem << char(179);
}
void ShowSingleMonHoc(MON_HOC* mh, int index) {
	cout << setw(3) << index + 1 << char(179) << setw(15) << mh->MAMH << char(179)
		<< setw(30) << mh->TENMH << char(179)
		<< setw(15) << mh->STCLT << char(179) << setw(15) << mh->STCTH << char(179);
}
// END DS DANG KY

int CommonShowSvList(DS_SINH_VIEN& ds_sv, int positionSubMenu, char* maLop = NULL) {
	int total = maLop ? countTotalSvByLop(ds_sv, maLop) : ds_sv.totalSv;
	SINH_VIEN** sv = CreateArraySV(total, sizeof(SINH_VIEN));
	if (maLop != NULL) {
		ConvertLinkedListSVBylop(ds_sv, sv, maLop);// TODO: bug occur here. Need to check and fix
	}
	else {
		ConvertLinkedListSV(ds_sv, sv);
	}
	return InDanhSachSinhVien(ds_sv, sv, total, 40, 10, positionSubMenu);
}
int InDanhSachMonHoc(DS_MON_HOC& ds_mh, int x, int y, int positionSubMenu) {
	cout << setfill(' ');

	SetColor(color_black | colorbk_white);
	gotoXY(x, y);
	cout << setw(3) << "STT" << char(179) << setw(15) << "MaMH" << char(179) << setw(30) << "Ten MH" << char(179)
		<< setw(15) << "So tin chi LT" << char(179) << setw(15) << "So tin chi TH" << char(179);

	int currentPage = 0, posActive = -1;
	int posPrint = 0;
	int perPage = 10;
	int totalPage = ds_mh.n / perPage;

	if (ds_mh.n % perPage != 0) {
		totalPage += 1;
	}

	int key = -1;

	perPage = perPage > ds_mh.n ? ds_mh.n : perPage;
	do {
		switch (key)
		{
		case key_F2: {
			// Prevent remove/update actions when show list students pos = 0
			if (positionSubMenu != 1 || posActive == -1) break;
			ConfirmDialog("Ban xac nhan xoa mon hoc ?");
			key = ControlMenu(&ActionConfirm, color_darkwhite, color_green);
			if (key == key_Enter && ActionConfirm.posStatus == 0) {
				RemoveMonHoc(ds_mh, ds_mh.ds[posActive + posPrint]->MAMH);
				UpdateFileDSMonHoc(ds_mh);
				clrscr(40, 5, 90, 30, ' '); // xoa tu vi tri form confirm remove
				return -1;
			}
			else {
				clrscr(40, 5, 90, 30, ' '); // xoa tu vi tri form confirm remove
				return -1;
			}
			goto paint;
			break;
		}
		case key_F3: {
			if (positionSubMenu != 1 || posActive == -1) break;
			// TODO: Init form to update student
			SetColor(color_darkwhite);
			string textFields[4] = { "" };
			int maxTexts[4] = { MAX_MAMH - 1, MAX_TENMH - 1, 4, 4 };
			textFields[0] = ds_mh.ds[posActive + posPrint]->MAMH;
			textFields[1] = ds_mh.ds[posActive + posPrint]->TENMH;
			std::ostringstream stcth, stclt;
			stcth << ds_mh.ds[posActive + posPrint]->STCTH;
			stclt << ds_mh.ds[posActive + posPrint]->STCLT;
			textFields[2] = stclt.str();
			textFields[3] = stcth.str();
			bool valid = true;
			int keyFormUpdate = -1;
			do
			{
				SetColor(color_white | colorbk_green);
				rectagle(45, 4, 65, 15);
				SetColor(color_white);
				keyFormUpdate = DrawFormInputMonHoc(70, 5, 30, textFields, maxTexts, 4, true);
				if (keyFormUpdate == key_Enter) {
					if (!CheckInputBoxIsNull(textFields, 4)) {
						// validate data
						MON_HOC* mh = new MON_HOC;
						strcpy_s(mh->MAMH, MAX_MAMH, textFields[0].c_str());
						strcpy_s(mh->TENMH, MAX_TENMH, textFields[1].c_str());
						mh->STCLT = atoi(textFields[2].c_str());
						mh->STCTH = atoi(textFields[3].c_str());
						UpdateMonHoc(ds_mh, mh);
						// TODO: need to update to file, after process testing done !
						UpdateFileDSMonHoc(ds_mh);

						gotoXY(60, 18);
						cout << "Cap nhat mon hoc thanh cong!";
						Sleep(1500);
						valid = true;
						clrscr(40, 4, 90, 35, ' ');
						return keyFormUpdate;
					}
					else {
						gotoXY(60, 18);
						cout << "Du lieu nhap khong duoc de trong!";
						Sleep(1500);
						valid = false;
					}
				}
				else if (keyFormUpdate == key_esc) {
					clrscr(40, 4, 90, 35, ' ');
					return key;
				}
			} while (!valid);
			break;
		}
		case key_Up: {
			if (posActive > 0) {

				SetColor(color_darkwhite);
				gotoXY(x, y + posActive + 1);
				ShowSingleMonHoc(ds_mh.ds[posActive + posPrint], posActive + posPrint);

				--posActive;


				SetColor(color_green);
				gotoXY(x, y + posActive + 1);
				ShowSingleMonHoc(ds_mh.ds[posActive + posPrint], posActive + posPrint);
				break;
			}
		}
		case key_Left: {
			if (posPrint - perPage >= 0) {
				posPrint -= perPage;
				--currentPage;
				posActive = perPage - 1;
			}
			goto paint;
		}
		case key_Down: {
			if (posActive < perPage - 1 && posActive + posPrint < ds_mh.n - 1) {
				if (posActive >= 0) {
					SetColor(color_darkwhite);
					gotoXY(x, y + posActive + 1);
					ShowSingleMonHoc(ds_mh.ds[posActive + posPrint], posActive + posPrint);
				}
				++posActive;

				SetColor(color_green);
				gotoXY(x, y + posActive + 1);
				ShowSingleMonHoc(ds_mh.ds[posActive + posPrint], posActive + posPrint);
				break;
			}
		}
		case key_Right: {
			if (posPrint + perPage < ds_mh.n) {
				posPrint += perPage;
				++currentPage;
				posActive = 0;
			}
			goto paint;
		}
		default: {
			goto paint;
		}
		   paint: {
			   int index = 0;
			   int indexitem;

			   SetColor(color_darkwhite);
			   for (; index < perPage; index++)
			   {
				   gotoXY(x, y + index + 1);
				   indexitem = index + posPrint;

				   if (indexitem >= ds_mh.n) break;
				   ShowSingleMonHoc(ds_mh.ds[indexitem], indexitem);
			   }

			   for (; index <= perPage; index++)
			   {
				   gotoXY(x, y + index + 1);
				   indexitem = index + posPrint;
				   cout << setw(90) << " ";
			   }

			   gotoXY(x, y + perPage + 2);
			   cout << currentPage + 1 << "/" << totalPage;
			   if (posActive >= 0) {
				   SetColor(color_green);
				   gotoXY(x, y + posActive + 1);
				   int index = posActive + posPrint;
				   ShowSingleMonHoc(ds_mh.ds[index], index);
			   }
			   break;
		}
		}
		key = inputKey();
	} while (key != key_esc);
	clrscr(40, 10, 90, 30, ' ');
	return key;
}
int InDanhSachLopTinChi(AppContext& context, Lop_Tin_Chi* ltc[], int n, int x, int y, int positionSubMenu, bool isStudent, bool isInsert) {
	cout << setfill(' ');

	SetColor(color_black | colorbk_white);
	gotoXY(x, y);
	cout << setw(3) << "STT" << char(179) << setw(10) << "MaLopTC" << char(179)
		<< setw(11) << "MaMH" << char(179) << setw(6) << "HOC KY" << char(179)
		<< setw(4) << "NHOM" << char(179) << setw(20) << "NIEN KHOA" << char(179)
		<< setw(7) << "SV MAX" << char(179) << setw(7) << "SV MIN" << char(179)
		<< setw(7) << "CON LAI" << char(179);

	int currentPage = 0, posActive = -1;
	int posPrint = 0;
	int perPage = 10;
	int totalPage = n / perPage;
	int selected = posActive + posPrint;
	if (n % perPage != 0) {
		totalPage += 1;
	}

	int key = -1;

	perPage = perPage > n ? n : perPage;
	do {
		switch (key)
		{
		case key_tab: {
			posActive = -1;
			return key;
		}
		case key_F1: {
			// TODO: Xử lý việc sinh viên đăng ký lớp tín chỉ
			if (isStudent) {
				SV_DANG_KY* sv_dk = new SV_DANG_KY;
				strcpy_s(sv_dk->MASV, MAX_MASV, context.currentUser);
				if (isInsert && ltc[posActive + posPrint]) {
					if (ltc[posActive + posPrint]->sv_max == ltc[posActive + posPrint]->totalSvDK) {
						gotoXY(55, 39);
						cout << "Lop tin chi da full. Khong the dang ky!";
						Sleep(1000);
						clrscr(55, 39, 90, 2, ' ');
					}
					else {
						bool exist = CheckSvExistLTC(ltc[posActive + posPrint], context.currentUser);
						// TODO: sinh vien ko the dang ky LTC co chung monhoc, nien khoa, hoc ky, nhom => khac 1 tronng 4 
						if (!exist) {
							sv_dk->DIEM = -1;
							InsertLastDSDKY(ltc[posActive + posPrint]->ds_sv_dky, sv_dk);
							ltc[posActive + posPrint]->totalSvDK++;
							UpdateNodeOfTree(context.tree, ltc[posActive + posPrint]);
							context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
							context.nLTC = 0;
							ConvertTreeToArray(context.tree, context.ds, context.nLTC);
							UpdateListLopTinChiToFile(context.ds, context.nLTC);
							return key;
						}
						else {
							gotoXY(55, 39);
							cout << "Lop tin chi da duoc dang ky!";
							Sleep(1000);
							clrscr(55, 39, 90, 2, ' ');
						}
					}
				}
				else if (!isInsert) {
					if (posActive + posPrint >= 0) {
						// TODO: remove sv inside ltc
						bool hasScore = CheckSvHasScore(ltc[posActive + posPrint]->ds_sv_dky, sv_dk->MASV);
						if (hasScore) {
							gotoXY(55, 39);
							cout << "Sinh vien da ton tai diem. Khong the huy dang ky LTC nay!";
							Sleep(1000);
							clrscr(55, 39, 90, 2, ' ');
						}
						else {
							int result = RemoveSV_Dang_Ky_ByMSSV(ltc[posActive + posPrint]->ds_sv_dky, sv_dk->MASV);
							if (result == -1) {
								gotoXY(55, 39);
								cout << "Danh sach dang rong. Khong the thuc hien chuc nang nay!";
								Sleep(1000);
								clrscr(55, 39, 90, 2, ' ');
							}
							else {
								gotoXY(60, 35);
								cout << "Xoa lop tin chi thanh cong!";
								ltc[posActive + posPrint]->totalSvDK--;
								UpdateNodeOfTree(context.tree, ltc[posActive + posPrint]);
								context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
								context.nLTC = 0;
								ConvertTreeToArray(context.tree, context.ds, context.nLTC);
								UpdateListLopTinChiToFile(context.ds, context.nLTC);
								Sleep(1000);
								clrscr(40, 25, 100, 15, ' ');
								return key;
							}
						}
						break;
					}
					else {
						SetColor(color_green);
						gotoXY(55, 39);
						cout << "Danh sach dang rong. Khong the thuc hien chuc nang nay!";
						Sleep(1500);
						clrscr(55, 39, 90, 2, ' ');
						break;
					}
				}
			}
			break;
		}
		case key_F2: {
			// Prevent remove/update actions when show list ltc pos = 0
			if (positionSubMenu != 1 || posActive == -1) break;
			ConfirmDialog("Ban xac nhan xoa LTC ?");
			key = ControlMenu(&ActionConfirm, color_darkwhite, color_green);
			if (key == key_Enter && ActionConfirm.posStatus == 0) {
				// TODO: need to check in ltc exist student has score, if exist => can't remove !
				RemoveNodeOfTree(context.tree, ltc[posActive + posPrint]->MALOPTC, n);
				n--;
				context.ds = CreateArrayLopTinChi(n, sizeof(Lop_Tin_Chi));
				context.nLTC = 0;
				ConvertTreeToArray(context.tree, context.ds, context.nLTC);
				UpdateListLopTinChiToFile(context.ds, context.nLTC);
				clrscr(40, 5, 100, 35, ' '); // xoa tu vi tri form confirm remove
				return -1;
			}
			else {
				clrscr(40, 5, 100, 35, ' '); // xoa tu vi tri form confirm remove
				return -1;
			}
			break;
		}
		case key_F3: {
			if (positionSubMenu != 1 || posActive == -1) break;
			// TODO: Init form to update lop tin chi
			SetColor(color_darkwhite);
			string textFields[7] = { "" };
			int maxTexts[7] = { 3, MAX_MAMH - 1, MAX_NIENKHOA - 1, 3, 3, 3, 3 };
			textFields[1] = ltc[posActive + posPrint]->MAMH;
			textFields[2] = ltc[posActive + posPrint]->NIEN_KHOA;

			std::ostringstream maLTC, hocky, nhom, sv_max, sv_min;
			maLTC << ltc[posActive + posPrint]->MALOPTC;
			hocky << ltc[posActive + posPrint]->HOC_KY;
			nhom << ltc[posActive + posPrint]->NHOM;
			sv_max << ltc[posActive + posPrint]->sv_max;
			sv_min << ltc[posActive + posPrint]->sv_min;
			textFields[0] = maLTC.str();
			textFields[3] = hocky.str();
			textFields[4] = nhom.str();
			textFields[5] = sv_max.str();
			textFields[6] = sv_min.str();
			bool valid = true;
			int keyFormUpdate = -1;
			do
			{
				SetColor(color_white | colorbk_green);
				rectagle(45, 4, 65, 25);
				SetColor(color_white);
				keyFormUpdate = DrawFormInputLTC(70, 5, 30, textFields, maxTexts, 7, true);
				if (keyFormUpdate == key_Enter) {
					if (!CheckInputBoxIsNull(textFields, 7)) {
						// validate data
						Lop_Tin_Chi* p = new Lop_Tin_Chi;
						p->MALOPTC = atoi(textFields[0].c_str());
						strcpy_s(p->MAMH, MAX_MAMH, textFields[1].c_str());
						strcpy_s(p->NIEN_KHOA, MAX_NIENKHOA, textFields[2].c_str());
						p->HOC_KY = atoi(textFields[3].c_str());
						p->NHOM = atoi(textFields[4].c_str());
						p->sv_max = atoi(textFields[5].c_str());
						p->sv_min = atoi(textFields[6].c_str());
						bool exist = CheckExistMaMH(context.ds_mh, p->MAMH);
						if (!exist) {
							gotoXY(60, 27);
							cout << "Ma mon hoc khong ton tai. Kiem tra lai !";
							Sleep(1500);
							valid = false;
						}
						else {
							if (CheckLopTinChiToUpdate(ltc, n, p)) {
								gotoXY(60, 27);
								cout << "Thong tin cap nhat da ton tai. Kiem tra lai !";
								Sleep(1500);
								valid = false;
							}
							else if (p->sv_min <= 0 || p->sv_min > p->sv_max) {
								gotoXY(60, 27);
								cout << "SV min > 0, va < SV max. Kiem tra lai!";
								Sleep(1500);
								valid = false;
							}
							else {
								UpdateNodeOfTree(context.tree, p);
								UpdateListLopTinChiToFile(ltc, n);
								delete p;
								gotoXY(60, 27);
								cout << "Cap nhat lop tin chi thanh cong!";
								Sleep(1500);
								clrscr(40, 4, 100, 35, ' ');
								valid = true;
								return keyFormUpdate;
							}
						}

					}
					else {
						gotoXY(60, 36);
						cout << "Du lieu nhap khong duoc de trong!";
						Sleep(1500);
						valid = false;
					}
				}
				else if (keyFormUpdate == key_esc) {
					clrscr(40, 4, 100, 35, ' ');
					return key;
				}
			} while (!valid);
			break;
		}
		case key_Up: {
			if (posActive > 0) {

				SetColor(color_darkwhite);
				gotoXY(x, y + posActive + 1);
				ShowSingleLTC(ltc[posActive + posPrint], posActive + posPrint);

				--posActive;


				SetColor(color_green);
				gotoXY(x, y + posActive + 1);
				ShowSingleLTC(ltc[posActive + posPrint], posActive + posPrint);
				break;
			}

		}
		case key_Left: {
			if (posPrint - perPage >= 0) {
				posPrint -= perPage;
				if (n > 0) {
					--currentPage;
				}
				posActive = perPage - 1;
			}
			goto paint;
		}
		case key_Down: {
			if (posActive < perPage - 1 && posActive + posPrint < n - 1) {
				if (posActive >= 0) {
					SetColor(color_darkwhite);
					gotoXY(x, y + posActive + 1);
					ShowSingleLTC(ltc[posActive + posPrint], posActive + posPrint);
				}
				++posActive;

				SetColor(color_green);
				gotoXY(x, y + posActive + 1);
				ShowSingleLTC(ltc[posActive + posPrint], posActive + posPrint);
				break;
			}
		}
		case key_Right: {
			if (posPrint + perPage < n) {
				posPrint += perPage;
				++currentPage;
				posActive = 0;
			}
			goto paint;
		}
		default: {
			goto paint;
		}
		   paint: {
			   int index = 0;
			   int indexitem;

			   SetColor(color_darkwhite);
			   for (; index < perPage; index++)
			   {
				   gotoXY(x, y + index + 1);
				   indexitem = index + posPrint;

				   if (indexitem >= n) break;
				   ShowSingleLTC(ltc[indexitem], indexitem);
			   }

			   for (; index <= perPage; index++)
			   {
				   gotoXY(x, y + index + 1);
				   indexitem = index + posPrint;
				   cout << setw(90) << " ";
			   }

			   gotoXY(x, y + perPage + 1);
			   cout << currentPage + 1 << "/" << totalPage;
			   if (posActive >= 0) {
				   SetColor(color_green);
				   gotoXY(x, y + posActive + 1);
				   ShowSingleLTC(ltc[posActive + posPrint], posActive + posPrint);
			   }
			   break;
		}
		}
		key = inputKey();
	} while (key != key_esc);
	if (isStudent && !isInsert) return key;
	clrscr(30, 10, 100, 30, ' ');
	return key;
}
int InDanhSachSinhVien(DS_SINH_VIEN& ctx_ds_sv, SINH_VIEN* ds_sv[], int n, int x, int y, int positionSubMenu) {
	cout << setfill(' ');

	SetColor(color_black | colorbk_white);
	gotoXY(x, y);
	cout << setw(3) << "STT" << char(179) << setw(15) << "Ma Lop" << char(179) << setw(13) << "Ma SV" << char(179)
		<< setw(20) << "Ho" << char(179) << setw(15) << "Ten" << char(179)
		<< setw(5) << "Phai" << char(179) << setw(11) << "SDT" << char(179);

	int currentPage = 0, posActive = -1;
	int posPrint = 0;
	int perPage = 20;
	int totalPage = n / perPage;

	if (n % perPage != 0) {
		totalPage += 1;
	}

	int key = -1;

	perPage = perPage > n ? n : perPage;
	do {
		switch (key)
		{
		case key_F2: {
			// Prevent remove/update actions when show list students pos = 0
			if (positionSubMenu != 1 || posActive == -1) break;
			ConfirmDialog("Ban xac nhan xoa SV ?");
			key = ControlMenu(&ActionConfirm, color_darkwhite, color_green);
			if (key == key_Enter && ActionConfirm.posStatus == 0) {
				RemoveSvByMSSV(ctx_ds_sv, ds_sv[posActive + posPrint]->MASV);
				//UpdateListStudentToFile(ctx_ds_sv);
				clrscr(40, 5, 90, 30, ' '); // xoa tu vi tri form confirm remove
				return -1;
			}
			else {
				clrscr(40, 5, 90, 30, ' '); // xoa tu vi tri form confirm remove
				return -1;
			}
			break;
		}
		case key_F3: {
			if (positionSubMenu != 1 || posActive == -1) break;
			// TODO: Init form to update student
			SetColor(color_darkwhite);
			string textFields[7] = { "" };
			int maxTexts[7] = { MAX_MALOP - 1, MAX_MASV - 1,
				MAX_HO - 1,MAX_TEN - 1, MAX_PHAI - 1,MAX_SDT - 1,4 };
			textFields[0] = ds_sv[posActive + posPrint]->MASV;
			textFields[1] = ds_sv[posActive + posPrint]->MALOP;
			textFields[2] = ds_sv[posActive + posPrint]->HO;
			textFields[3] = ds_sv[posActive + posPrint]->TEN;
			textFields[4] = ds_sv[posActive + posPrint]->PHAI;
			textFields[5] = ds_sv[posActive + posPrint]->SDT;
			std::ostringstream ss;
			ss << ds_sv[posActive + posPrint]->NAMNHAPHOC;
			textFields[6] = ss.str();
			bool valid = true;
			int keyFormUpdate = -1;
			do
			{
				SetColor(color_white | colorbk_green);
				rectagle(45, 4, 65, 25);
				SetColor(color_white);
				keyFormUpdate = DrawFormInputSinhVien(70, 5, 30, textFields, maxTexts, 7, true);
				if (keyFormUpdate == key_Enter) {
					if (!CheckInputBoxIsNull(textFields, 7)) {
						// validate data
						SINH_VIEN* sv = new SINH_VIEN;
						strcpy_s(sv->MASV, MAX_MASV, textFields[0].c_str());
						strcpy_s(sv->MALOP, MAX_MALOP, textFields[1].c_str());
						strcpy_s(sv->HO, MAX_HO, textFields[2].c_str());
						strcpy_s(sv->TEN, MAX_TEN, textFields[3].c_str());
						strcpy_s(sv->PHAI, MAX_PHAI, textFields[4].c_str());
						strcpy_s(sv->SDT, MAX_SDT, textFields[5].c_str());
						sv->NAMNHAPHOC = atoi(textFields[6].c_str());
						bool exist = CheckExistLop(sv->MALOP);
						if (!exist) {
							InsertLopIntoDSLop(sv->MALOP);
						}
						UpdateSinhVien(ctx_ds_sv, sv);
						UpdateListStudentToFile(ctx_ds_sv);

						gotoXY(60, 27);
						cout << "Cap nhat sinh vien thanh cong!";
						Sleep(1500);
						clrscr(40, 4, 90, 35, ' ');
						valid = true;
						return keyFormUpdate;
					}
					else {
						gotoXY(60, 27);
						cout << "Du lieu nhap khong duoc de trong!";
						Sleep(1500);
						valid = false;
					}
				}
				else if (keyFormUpdate == key_esc) {
					clrscr(40, 4, 90, 35, ' ');
					return key;
				}
			} while (!valid);
			break;
		}
		case key_Up: {
			if (posActive > 0) {

				SetColor(color_darkwhite);
				gotoXY(x, y + posActive + 1);
				ShowSingleSV(ds_sv[posActive + posPrint], posActive + posPrint);

				--posActive;


				SetColor(color_green);
				gotoXY(x, y + posActive + 1);
				ShowSingleSV(ds_sv[posActive + posPrint], posActive + posPrint);
				break;
			}
		}
		case key_Left: {
			if (posPrint - perPage >= 0) {
				posPrint -= perPage;
				--currentPage;
				posActive = perPage - 1;
			}
			goto paint;
		}
		case key_Down: {
			if (posActive < perPage - 1 && posActive + posPrint < n - 1) {
				if (posActive >= 0) {
					SetColor(color_darkwhite);
					gotoXY(x, y + posActive + 1);
					ShowSingleSV(ds_sv[posActive + posPrint], posActive + posPrint);
				}
				++posActive;

				SetColor(color_green);
				gotoXY(x, y + posActive + 1);
				ShowSingleSV(ds_sv[posActive + posPrint], posActive + posPrint);
				break;
			}
		}
		case key_Right: {
			if (posPrint + perPage < n) {
				posPrint += perPage;
				++currentPage;
				posActive = 0;
			}
			goto paint;
		}
		default: {
			goto paint;
		}
		   paint: {
			   int index = 0;
			   int indexitem;

			   SetColor(color_darkwhite);
			   for (; index < perPage; index++)
			   {
				   gotoXY(x, y + index + 1);
				   indexitem = index + posPrint;

				   if (indexitem >= n) break;
				   ShowSingleSV(ds_sv[indexitem], indexitem);
			   }

			   for (; index <= perPage; index++)
			   {
				   gotoXY(x, y + index + 1);
				   indexitem = index + posPrint;
				   cout << setw(90) << " ";
			   }

			   gotoXY(x, y + perPage + 3);
			   cout << "Page " << currentPage + 1 << "/" << totalPage;
			   if (posActive >= 0) {
				   SetColor(color_green);
				   gotoXY(x, y + posActive + 1);
				   ShowSingleSV(ds_sv[posActive + posPrint], posActive + posPrint);
			   }
			   break;
		}
		}
		key = inputKey();
	} while (key != key_esc);
	clrscr(40, 10, 90, 30, ' ');
	return key;
}
int InDanhSachSinhVien_Diem(SV_DIEM* ds_sv_diem[], int n, int x, int y) {
	cout << setfill(' ');

	SetColor(color_black | colorbk_white);
	gotoXY(x, y);
	cout << setw(3) << "STT" << char(179) << setw(15) << "Ma Sinh Vien" << char(179)
		<< setw(20) << "Ho" << char(179) << setw(15) << "Ten" << char(179) << setw(5) << "Diem" << char(179);

	int currentPage = 0, posActive = -1;
	int posPrint = 0;
	int perPage = 5;
	int totalPage = n / perPage;

	if (n % perPage != 0) {
		totalPage += 1;
	}

	int key = -1;

	perPage = perPage > n ? n : perPage;
	do {
		switch (key)
		{
		case key_F3: {
			if (posActive == -1) break;
			// TODO: Init form to update student
			SetColor(color_darkwhite);
			string textFields[1] = { "" };
			int maxTexts[1] = { 4 };
			textFields[0] = ds_sv_diem[posActive + posPrint]->diem;
			std::ostringstream ss;
			ss << ds_sv_diem[posActive + posPrint]->diem;
			textFields[0] = ss.str();
			bool valid = true;
			int keyFormUpdate = -1;
			do
			{
				SetColor(color_white | colorbk_green);
				rectagle(60, 10, 30, 7);
				keyFormUpdate = DrawFormInputDiem(75, 10, 10, textFields, maxTexts);
				if (keyFormUpdate == key_Enter) {
					if (!CheckInputBoxIsNull(textFields, 1)) {
						float score = atof(textFields[0].c_str());
						if (score > -2 && score <= 10) {
							ds_sv_diem[posActive + posPrint]->diem = score;
							gotoXY(62, 16);
							cout << "Cap nhat diem thanh cong!";
							Sleep(1500);
							clrscr(40, 10, 90, 30, ' ');
							valid = true;
							return keyFormUpdate;
						}
						else {
							gotoXY(62, 16);
							cout << "Diem khong hop le!";
							Sleep(1500);
							valid = false;
						}
					}
					else {
						SetColor(color_red);
						gotoXY(62, 16);
						cout << "Diem khong duoc de trong!";
						Sleep(1500);
						valid = false;
					}
					// TODO: check score enter invalid => >-1    <10
				}
				else if (keyFormUpdate == key_esc) {
					clrscr(40, 10, 90, 30, ' ');
					return key;
				}
			} while (!valid);
			break;
			break;
		}
		case key_Up: {
			if (posActive > 0) {

				SetColor(color_darkwhite);
				gotoXY(x, y + posActive + 1);
				ShowSingleSV_Diem(ds_sv_diem[posActive + posPrint], posActive + posPrint);

				--posActive;


				SetColor(color_green);
				gotoXY(x, y + posActive + 1);
				ShowSingleSV_Diem(ds_sv_diem[posActive + posPrint], posActive + posPrint);
				break;
			}
		}
		case key_Left: {
			if (posPrint - perPage >= 0) {
				posPrint -= perPage;
				--currentPage;
				posActive = perPage - 1;
			}
			goto paint;
		}
		case key_Down: {
			if (posActive < perPage - 1 && posActive + posPrint < n - 1) {
				if (posActive >= 0) {
					SetColor(color_darkwhite);
					gotoXY(x, y + posActive + 1);
					ShowSingleSV_Diem(ds_sv_diem[posActive + posPrint], posActive + posPrint);
				}
				++posActive;

				SetColor(color_green);
				gotoXY(x, y + posActive + 1);
				ShowSingleSV_Diem(ds_sv_diem[posActive + posPrint], posActive + posPrint);
				break;
			}
		}
		case key_Right: {
			if (posPrint + perPage < n) {
				posPrint += perPage;
				++currentPage;
				posActive = 0;
			}
			goto paint;
		}
		default: {
			goto paint;
		}
		   paint: {
			   int index = 0;
			   int indexitem;

			   SetColor(color_darkwhite);
			   for (; index < perPage; index++)
			   {
				   gotoXY(x, y + index + 1);
				   indexitem = index + posPrint;

				   if (indexitem >= n) break;
				   ShowSingleSV_Diem(ds_sv_diem[indexitem], indexitem);
			   }

			   for (; index <= perPage; index++)
			   {
				   gotoXY(x, y + index + 1);
				   indexitem = index + posPrint;
				   cout << setw(90) << " ";
			   }

			   gotoXY(x, y + perPage + 3);
			   cout << "Page " << currentPage + 1 << "/" << totalPage;
			   if (posActive >= 0) {
				   SetColor(color_green);
				   gotoXY(x, y + posActive + 1);
				   ShowSingleSV_Diem(ds_sv_diem[posActive + posPrint], posActive + posPrint);
			   }
			   break;
		}
		}
		key = inputKey();
	} while (key != key_esc);
	clrscr(40, 10, 90, 30, ' ');
	return key;
}
#endif // !STRUCTURE_CPP
