﻿#include <iostream>;
#include <string>;
#include <string.h>;
#include <stdio.h>;
#include <fstream>;
#include <cstdlib>;
#include <ctime>;
using namespace std;

// define constant for quantity of subject
constexpr auto MAX_MON_HOC = 300;

// ===== BEGIN MON HOC =====
struct mon_hoc
{
	char MAMH[12];
	char TENMH[256];
	int STCLT;
	int STCTH;
};
typedef struct mon_hoc MON_HOC;

struct ds_monhoc
{
	MON_HOC* ds[MAX_MON_HOC];
	int n = 0;
};
typedef struct ds_monhoc DS_MON_HOC;
// ===== END MON HOC =====

// ===== BEGIN SINH VIEN =====
struct sinh_vien
{
	// data
	char MASV[12];
	char PHAI[4];
	char SDT[25];
	char MALOP[15];
	string HO;
	string TEN;
	int NAMNHAPHOC;
	// pointer
	sinh_vien* pNext;
};
typedef struct sinh_vien SINH_VIEN;

struct ds_sinh_vien
{
	SINH_VIEN* pHead = NULL;
	SINH_VIEN* pTail = NULL;
};
typedef struct ds_sinh_vien DS_SINH_VIEN;
// ===== END SINH VIEN =====

// ===== BEGIN LOP TIN CHI =====
struct lop_tin_chi
{
	// data
	int MALOPTC;
	char MAMH[12];
	char NIEN_KHOA[20];
	int HOC_KY;
	int NHOM;
	int sv_max;
	int sv_min;
	DS_SINH_VIEN ds_sv;

	// pointer
	lop_tin_chi* pLeft;
	lop_tin_chi* pRight;
};
typedef struct lop_tin_chi Lop_Tin_Chi;
typedef Lop_Tin_Chi* TREE;

struct ds_lop_tin_chi
{
	TREE tree = NULL;
};
typedef struct ds_lop_tin_chi DS_LOP_TIN_CHI;
// ===== END LOP TIN CHI =====

// ===== BEGIN DS DANG KY =====
struct dang_ky
{
	// data
	char MASV[12];
	float DIEM;
	// pointer
	dang_ky* pNext;
};
typedef struct dang_ky DANG_KY;

struct ds_dang_ky
{
	DANG_KY* pHead = NULL;
	int n = 0;
};
typedef struct dang_ky DS_DANG_KY;
// ===== END DS DANG KY =====

// ===== BEGIN HELPER =====

void SortString() {}

bool CheckExistMSSV(DS_SINH_VIEN ds_sv, char* massv)
{
	bool exist = false;
	for (SINH_VIEN* k = ds_sv.pHead; k != NULL; k = k->pNext)
	{
		if (_strcmpi(k->MASV, massv) == 0)
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
	if (tree->MALOPTC == maLopTc) {
		return false;
	}
	else if (tree->MALOPTC > maLopTc) {
		CheckExistMaLTC(tree->pRight, maLopTc);
	}
	else if (tree->MALOPTC < maLopTc) {
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
	string randomId = "MSSV0000";
	char cloned[12];
	// max 11 ki tu, con lai chua ki tu ket thuc chuoi.
	strcpy_s(cloned, 11, randomId.c_str());
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
	string randomId = "MH0000";
	char cloned[12];
	// max 11 ki tu, con lai chua ki tu ket thuc chuoi.
	strcpy_s(cloned, 11, randomId.c_str());
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
		maLopTc = rand() * (999 - 100 + 1) + 100;
	} while (CheckExistMaLTC(tree, maLopTc));
	return maLopTc;
}
// ===== END HELPER =====

// ===== BEGIN DS LOP TIN CHI =====
void InitDSLopTinChi(DS_LOP_TIN_CHI& ds_ltc) {
	ds_ltc.tree = NULL;
}

Lop_Tin_Chi* InitNodeDSLTC() {
	Lop_Tin_Chi* p = new Lop_Tin_Chi;

	p->pLeft = NULL;
	p->pRight = NULL;
	return p;
}

void InsertNodeIntoTree(TREE& tree, Lop_Tin_Chi* data) {
	if (tree == NULL) {
		tree = data;
	}
	else {
		if (tree->MALOPTC > data->MALOPTC) {
			InsertNodeIntoTree(tree->pLeft, data);
		}
		else if (tree->MALOPTC < data->MALOPTC) {
			InsertNodeIntoTree(tree->pRight, data);
		}
	}
}

void InportDSLopTC(DS_LOP_TIN_CHI& ds) {
	// TODO: MALOPTC must be auto generate by integer.
	for (int i = 0; i < 2; i++)
	{
		cout << "\n====== Nhap lop tin chi thu " << i + 1 << " ======" << endl;
		Lop_Tin_Chi* p = InitNodeDSLTC();
		p->MALOPTC = RandomIDLTC(ds.tree);
		cout << "\nNhap ma mon hoc: "; gets_s(p->MAMH);
		cout << "Nhap nien khoa: "; gets_s(p->NIEN_KHOA);
		cout << "Nhap hoc ky: "; cin >> p->HOC_KY;
		cout << "Nhap max sinh vien: "; cin >> p->sv_max;
		cout << "Nhap min sinh vien: "; cin >> p->sv_min;
		cout << "Nhap nhom:"; cin >> p->NHOM;
		InsertNodeIntoTree(ds.tree, p);
		i++;
	}
}

void ConvertTreeToArray(TREE t, Lop_Tin_Chi* ds[], int& n) {
	if (t != NULL) {
		ds[n] = new Lop_Tin_Chi;
		strcpy_s(ds[n]->MAMH, t->MAMH);
		strcpy_s(ds[n]->NIEN_KHOA, t->NIEN_KHOA);
		ds[n]->MALOPTC = t->MALOPTC;
		ds[n]->HOC_KY = t->HOC_KY;
		ds[n]->NHOM = t->NHOM;
		ds[n]->sv_max = t->sv_max;
		ds[n]->sv_min = t->sv_min;
		// TODO: Ds sinh viên đăng ký vào lớp tín chỉ này
		n++;
		ConvertTreeToArray(t->pLeft, ds, n);
		ConvertTreeToArray(t->pRight, ds, n);
	}
}
// Memory release of ds lopTC when we have finished displaying. Place bellow at ShowDSLopTinChi()
void MemoryReleaseDSLopTC(Lop_Tin_Chi* ds[], int n) {
	for (int i = 0; i < n; i++)
	{
		delete ds[i];
	}
}
void ShowDSLopTinChi(Lop_Tin_Chi* ds[], int n) {
	for (int i = 0; i < n; i++)
	{
		cout << "\nMa lop tin chi: " << ds[i]->MALOPTC << endl;
		cout << "Ma mon hoc: " << ds[i]->MAMH << endl;
		cout << "Nien khoa: " << ds[i]->NIEN_KHOA << endl;
		cout << "Hoc ky: " << ds[i]->HOC_KY << endl;
		cout << "Nhom: " << ds[i]->NHOM << endl;
		cout << "Max sinh vien: " << ds[i]->sv_max << endl;
		cout << "Min sinh vien: " << ds[i]->sv_min << endl;
	}
}

void RemoveLopTinChiById(TREE& t, int maLopTC) {
	if (t != NULL) {
		if (t->MALOPTC == maLopTC) {
			Lop_Tin_Chi* x = t;
			if (t->pLeft == NULL) {
				t = t->pRight;
			}
			else if (t->pRight == NULL) {
				t = t->pLeft;
			}
			else if (t->pLeft == NULL && t->pRight != NULL) {
				// Node the mang
				Node_Replaced_Tree(t->pRight, x);
			}
			delete x;
		}
		else if (t->MALOPTC > maLopTC) {
			RemoveLopTinChiById(t->pLeft, maLopTC);
		}
		else if (t->MALOPTC < maLopTC) {
			RemoveLopTinChiById(t->pRight, maLopTC);
		}
	}
}

void Node_Replaced_Tree(TREE& t, Lop_Tin_Chi*& lopTC) {
	if (t->pLeft != NULL) {
		Node_Replaced_Tree(t, lopTC);
	}
	else {
		// Swap_Node_Replaced(t, lopTC); TODO:
		lopTC = t;
		t = t->pRight;
	}
}

// ===== END DS LOP TIN CHI =====

// SINH VIEN
void Init_DS_Sinh_Vien(DS_SINH_VIEN& ds)
{
	ds.pHead = NULL;
	ds.pTail = NULL;
}

bool isEmptyDSSV(DS_SINH_VIEN ds_sv)
{
	if (ds_sv.pHead == NULL && ds_sv.pTail == NULL)
		return true;
	return false;
}

// Insert and order by MALOP+MASV
void InsertLastSv(DS_SINH_VIEN& ds_sinh_vien, SINH_VIEN* sv)
{
	if (ds_sinh_vien.pHead == NULL)
	{
		ds_sinh_vien.pHead = ds_sinh_vien.pTail = sv;
	}
	else
	{
		ds_sinh_vien.pTail->pNext = sv;
		ds_sinh_vien.pTail = sv;
		sv->pNext = NULL;
	}
}

void InsertFirstSv(DS_SINH_VIEN& ds_sv, SINH_VIEN* sv)
{
	if (ds_sv.pHead == NULL)
	{
		ds_sv.pHead = ds_sv.pTail = sv;
	}
	else
	{
		sv->pNext = ds_sv.pHead;
		ds_sv.pHead = sv;
	}
}

void RemoveFirst(DS_SINH_VIEN& ds_sv)
{
	SINH_VIEN* p;
	if (ds_sv.pHead == NULL)
		return;

	p = ds_sv.pHead;
	ds_sv.pHead = p->pNext;
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
	for (SINH_VIEN* k = ds_sv.pHead; k != NULL; k = k->pNext)
	{
		if (k->pNext == ds_sv.pTail)
		{
			delete ds_sv.pTail;
			k->pNext = NULL;
			ds_sv.pTail = k;
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
	if (_strcmpi(ds_sv.pHead->MASV, massv) == 0)
	{
		RemoveFirst(ds_sv);
		cout << "Xoa thanh cong vi tri dau tien" << endl;
		system("pause");
		return;
	}
	if (_strcmpi(ds_sv.pTail->MASV, massv) == 0)
	{
		RemoveLast(ds_sv);
		cout << "Xoa thanh cong vi tri cuoi cung trong ds" << endl;
		system("pause");
		return;
	}
	bool exists = false;
	SINH_VIEN* g = new SINH_VIEN;
	for (SINH_VIEN* k = ds_sv.pHead; k != NULL; k = k->pNext)
	{
		if (_strcmpi(k->MASV, massv) == 0)
		{
			exists = true;
			g->pNext = k->pNext;
			delete k;
			cout << "Xoa thanh cong" << endl;
			system("pause");
			return;
		}
		g = k;
	}
	if (!exists)
		cout << "\nKhong tim thay sinh vien" << endl;
}

void Input_Sinh_Vien(DS_SINH_VIEN& ds_sinh_vien)
{
	int slsv;
	int count = 0;
	char maLop[15];
	cout << "Nhap sl sv: ";
	cin >> slsv;
	cin.ignore();
	cout << "\nNhap ma lop: ";
	gets_s(maLop);
	do
	{
		SINH_VIEN* sv = new SINH_VIEN;
		if (sv == NULL)
		{
			cout << "Cap phat vung nho de khoi tao sv that bai." << endl;
			system("pause");
			return;
		}
		cout << "\nNhap ho: ";
		getline(cin, sv->HO);
		cout << "\nNhap ten: ";
		getline(cin, sv->TEN);
		cout << "\nNhap gioi tinh: ";
		gets_s(sv->PHAI);
		cout << "\nNhap so dien thoai: ";
		gets_s(sv->SDT);
		cout << "\nNhap nam hoc: ";
		cin >> sv->NAMNHAPHOC;
		strcpy_s(sv->MALOP, 15, maLop);
		cin.ignore();
		strcpy_s(sv->MASV, 12, RandomID(ds_sinh_vien).c_str());
		sv->pNext = NULL;
		InsertFirstSv(ds_sinh_vien, sv);
		count++;
	} while (count < slsv);
}

void Show_DS_Sinh_Vien(DS_SINH_VIEN ds_sv)
{
	int total = 0;
	for (SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		cout << "========== SINH VIEN " << ++total << " ==========" << endl;
		cout << "Ma lop: " << p->MALOP << endl;
		cout << "Ma SV: " << p->MASV << endl;
		cout << "Nam nhap hoc: " << p->NAMNHAPHOC << endl;
		cout << "Phai: " << p->PHAI << endl;
		cout << "So dien thoai: " << p->SDT << endl;
		cout << "Ho ten: " << p->HO << " " << p->TEN << endl;
	}
}

//  END SINH VIEN

// MON HOC
void Insert_MonHoc(DS_MON_HOC& ds_mon_hoc)
{
	for (int i = 0; i < 2; i++)
	{
		MON_HOC* monhoc = new MON_HOC;
		strcpy_s(monhoc->MAMH, 11, RandomIDMH(ds_mon_hoc).c_str());
		cout << "\nNhap vao ten mon hoc:";
		gets_s(monhoc->TENMH);
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
			ds_mon_hoc.ds[i] = ds_mon_hoc.ds[i + 1];
		}
		ds_mon_hoc.n--;
	}
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
// END MON HOC

// HANDLE FILES

void Read_File_MonHoc(DS_MON_HOC& ds_mon_hoc)
{
	ifstream fileIn;
	fileIn.open("C:\\Users\\Nguyen Dai\\source\\repos\\QLDIEMSV_HTC\\QLDIEMSV_HTC\\DS_MONHOC.txt", ios_base::in);
	if (fileIn.fail())
	{
		cout << "Open file (DS_MONHOC.txt) failed. Please check and update path of file again !!!" << endl;
		return;
	};
	while (!fileIn.eof())
	{
		char s[1];
		MON_HOC* data = new MON_HOC;
		fileIn.getline(data->MAMH, 12, ',');
		fileIn.getline(data->TENMH, 256, ',');
		fileIn >> data->STCLT;
		fileIn.ignore(1); // bỏ qua một ký tự
		fileIn >> data->STCTH;
		fileIn.getline(s, 1, '\n');
		fileIn.ignore();
		/*cout << "Ma MH:" << data->MAMH << " -> Ten MH:"
			<< data->TENMH << " -> So TCLT:"
			<< data->STCLT << " -> So TCTH:"<< data->STCTH << endl;*/
		ds_mon_hoc.ds[ds_mon_hoc.n] = data;
		ds_mon_hoc.n++;
	}
	fileIn.close();
}
// TODO:
void WriteFileMonHoc() {}

void ReadFileSinhVien(DS_SINH_VIEN& ds_sv)
{
	ifstream fileIn;
	fileIn.open("C:\\Users\\Nguyen Dai\\source\\repos\\QUANLY_DIEM_SV\\QUANLY_DIEM_SV\\DS_SINH_VIEN.txt", ios_base::in);
	if (fileIn.fail())
	{
		cout << "Open file (DS_SINH_VIEN.txt) failed. Please check and update path of file again !!!" << endl;
		return;
	};
	while (!fileIn.eof())
	{
		char s[1];
		SINH_VIEN* data = new SINH_VIEN;
		fileIn.getline(data->MALOP, 15, ',');
		fileIn.getline(data->MASV, 12, ',');
		getline(fileIn, data->HO, ',');
		getline(fileIn, data->TEN, ',');
		fileIn.getline(data->PHAI, 4, ',');
		fileIn.getline(data->SDT, 25, ',');
		fileIn >> data->NAMNHAPHOC;
		fileIn.getline(s, 1, '\n');
		InsertLastSv(ds_sv, data);
	}
	fileIn.close();
}

// END HANDLE FILES

int main()
{
	srand(time(NULL));
	DS_MON_HOC dsMonHoc;
	DS_SINH_VIEN dsSinhVien;
	DS_LOP_TIN_CHI dsLTC;
	Lop_Tin_Chi* ds[100];
	int n = 0;
	/*Init_DS_Sinh_Vien(dsSinhVien);
	Input_Sinh_Vien(dsSinhVien);
	Show_DS_Sinh_Vien(dsSinhVien);*/
	/*ReadFileSinhVien(dsSinhVien);

	char str[12];
	cout << "\nNhap massv:";
	cin.getline(str, 12);
	RemoveSvByMSSV(dsSinhVien, str);
	Show_DS_Sinh_Vien(dsSinhVien);*/
	//Insert_MonHoc(dsMonHoc);
	/*Read_File_MonHoc(dsMonHoc);*/
	//Show_DS_MonHoc(dsMonHoc);
	/*cout << "\n=======================" << endl;
	char mh[12];
	cout << "\nNhap ma mon hoc can xoa: ";
	gets_s(mh, 12);*/
	/*RemoveMonHoc(dsMonHoc, mh);
	Show_DS_MonHoc(dsMonHoc);*/
	InportDSLopTC(dsLTC);
	ConvertTreeToArray(dsLTC.tree, ds, n);
	ShowDSLopTinChi(ds, n);
	system("pause");
	return 0;
}