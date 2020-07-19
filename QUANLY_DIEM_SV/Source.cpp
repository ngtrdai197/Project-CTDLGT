#include <iostream>;
#include <string>;
#include <fstream>;
#include <ctime>;
#include "console.h";
#include "Menu.h";

using namespace std;
#define MAX_MON_HOC 300
#define MAX_MAMH 11
#define MAX_TENMH 100
#define MAX_MASV 13
#define MAX_PHAI 4
#define MAX_SDT 11
#define MAX_MALOP 16
#define MAX_HO 20
#define MAX_TEN 15
#define MAX_NIENKHOA 20

#define bk_blue 0x0030
#define red 0x0004

// ===== BEGIN MON HOC =====
struct mon_hoc
{
	char MAMH[MAX_MAMH];
	char TENMH[MAX_TENMH];
	float STCLT;
	float STCTH;
};
typedef struct mon_hoc MON_HOC;

struct ds_monhoc
{
	MON_HOC* ds[MAX_MON_HOC];
	int n;
};
typedef struct ds_monhoc DS_MON_HOC;
// ===== END MON HOC =====

// ===== BEGIN SINH VIEN =====
struct sinh_vien
{
	char MASV[MAX_MASV];
	char PHAI[MAX_PHAI];
	char SDT[MAX_SDT];
	char MALOP[MAX_MALOP];
	char HO[MAX_HO];
	char TEN[MAX_TEN];
	int NAMNHAPHOC;
};
typedef struct sinh_vien SINH_VIEN;
struct node_sinh_vien {
	SINH_VIEN data;
	node_sinh_vien* pNext;
};
typedef struct node_sinh_vien NODE_SINH_VIEN;

struct ds_sinh_vien
{
	NODE_SINH_VIEN* pHead = NULL;
	NODE_SINH_VIEN* pTail = NULL;
	int totalSv;
};
typedef struct ds_sinh_vien DS_SINH_VIEN;
// ===== END SINH VIEN =====

// ===== BEGIN LOP TIN CHI =====
struct lop_tin_chi
{
	int MALOPTC;
	char MAMH[MAX_MAMH];
	char NIEN_KHOA[MAX_NIENKHOA];
	int HOC_KY;
	int NHOM;
	int sv_max;
	int sv_min;
	DS_SINH_VIEN* ds_sv;
};
typedef struct lop_tin_chi Lop_Tin_Chi;
struct node_lop_tin_chi {
	Lop_Tin_Chi data;
	node_lop_tin_chi* pLeft;
	node_lop_tin_chi* pRight;
};
typedef struct node_lop_tin_chi NODE_LOP_TIN_CHI;
typedef NODE_LOP_TIN_CHI* TREE;

// ===== END LOP TIN CHI =====

// ===== BEGIN DS DANG KY =====
struct dang_ky
{
	// data
	char MASV[MAX_MASV];
	float DIEM;
	// pointer
	dang_ky* pNext;
};
typedef struct dang_ky DANG_KY;
struct ds_dang_ky
{
	DANG_KY* pHead = NULL;
	DANG_KY* pTail = NULL;
	int n;
};
typedef struct ds_dang_ky DS_DANG_KY;
// ===== END DS DANG KY =====

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
	string randomId = "MSMH000000";
	char cloned[11];
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
		maLopTc = rand() % (999 - 100 + 1) + 100;
	} while (CheckExistMaLTC(tree, maLopTc));
	return maLopTc;
}
int StringComparisions(char* a, char* b) {
	return _strcmpi(a, b);
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
		char temp[15];
		fileIn.getline(temp, 15, ',');
		if (_strcmpi(temp, malop) == 0) {
			exist = true;
			break;
		}
	}
	fileIn.close();
	return exist;
}
//template<class T>

class sv_test {
	char id[100];

	sv_test();
};
char** CreateArray(int x, int y) {
	char** a = new char* [y];
	for (int i = 0; i < y; i++)
	{
		a[i] = new char[x];
	}
	return a;
}
// ===== END HELPER =====

// HANDLE FILES
void Read_File_MonHoc(DS_MON_HOC& ds_mon_hoc)
{
	fstream fileIn;
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
		fileIn.getline(data->MAMH, MAX_MAMH, ',');
		fileIn.getline(data->TENMH, MAX_TENMH, ',');
		fileIn >> data->STCLT;
		fileIn >> data->STCTH;
		fileIn.ignore(); // bỏ qua một ký tự
		fileIn.getline(s, 1, '\n');
		/*cout << "Ma MH:" << data->MAMH << " -> Ten MH:"
			<< data->TENMH << " -> So TCLT:"
			<< data->STCLT << " -> So TCTH:"<< data->STCTH << endl;*/
		ds_mon_hoc.ds[ds_mon_hoc.n] = data;
		ds_mon_hoc.n++;
	}
	fileIn.close();
}
void WriteAStudentToFile(NODE_SINH_VIEN* sv) {
	ofstream fileOut;
	fileOut.open("DS_SINH_VIEN.txt", ios::out | ios::app);
	if (fileOut.fail())
	{
		cout << "Open file (DS_SINH_VIEN.txt) to write failed."
			<< "Please check and update path of file again !!!" << endl;
		return;
	};
	fileOut << endl << sv->data.MALOP << "," << sv->data.MASV << "," << sv->data.HO << ","
		<< sv->data.TEN << "," << sv->data.PHAI << "," << sv->data.SDT << "," << sv->data.NAMNHAPHOC;
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
		fileOut << endl << sv->data.MALOP << "," << sv->data.MASV << "," << sv->data.HO << ","
			<< sv->data.TEN << "," << sv->data.PHAI << "," << sv->data.SDT << "," << sv->data.NAMNHAPHOC;
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

		while (_strcmpi(trav->data.MALOP, nodeSV->data.MALOP) < 0 || _strcmpi(trav->data.MASV, nodeSV->data.MASV) < 0) {
			prev = trav;
			trav = trav->pNext;
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
			ds_sv.pTail->pNext = NULL;
		}
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
		char s[1];
		NODE_SINH_VIEN* node = new NODE_SINH_VIEN;
		fileIn.getline(node->data.MALOP, 17, ',');
		fileIn.getline(node->data.MASV, 14, ',');
		fileIn.getline(node->data.HO, 20, ',');
		fileIn.getline(node->data.TEN, 15, ',');
		fileIn.getline(node->data.PHAI, 4, ',');
		fileIn.getline(node->data.SDT, 25, ',');
		fileIn >> node->data.NAMNHAPHOC;
		fileIn.ignore();
		//fileIn.getline(s, 1, '\n');
		InsertAndSortSvIntoDS(ds_sv, node);
	}
	fileIn.close();
}

// DANH SACH DANG KY
void InsertLastDSDKY(DS_DANG_KY& ds_dk, DANG_KY* dk);
void ReadFileDS_DANG_KY(DS_DANG_KY& ds_dk)
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
		DANG_KY* node = new DANG_KY;
		fileIn.getline(node->MASV, MAX_MASV, ',');
		fileIn >> node->DIEM;
		fileIn.ignore();
		InsertLastDSDKY(ds_dk, node);
	}
	fileIn.close();
}

// END DANH SACH DANG KY

// TODO:
void UpdateListSvToLopTC(Lop_Tin_Chi*& ds, int totalLopTc, DS_SINH_VIEN& ds_sv_original, char* masvDKLTC[]) {
	for (int i = 0; i < totalLopTc; i++)
	{
		DS_SINH_VIEN* ds_sv = new DS_SINH_VIEN;
		for (NODE_SINH_VIEN* p = ds_sv_original.pHead; p != NULL; p = p->pNext)
		{
			for (int i = 0; i < 2; i++)
			{
				if (_strcmpi(p->data.MASV, masvDKLTC[i]) == 0) {
					InsertAndSortSvIntoDS(*ds_sv, p);
				}
			}
		}
		ds[i].ds_sv = ds_sv;
	}
}
void UpdateListLopTinChiToFile(Lop_Tin_Chi* ds, int n) {
	ofstream fileOut;
	fileOut.open("DS_LOP_TIN_CHI.txt", ios::out | ios::binary);
	if (fileOut.fail())
	{
		cout << "Open file (DS_LOP_TIN_CHI.txt) to write failed."
			<< "Please check and update path of file again !!!" << endl;
		return;
	};

	for (int i = 0; i < n; i++)
	{
		string masvDKLTC;
		for (NODE_SINH_VIEN* p = ds[i].ds_sv->pHead; p != NULL; p = p->pNext) {
			masvDKLTC += (string)p->data.MASV;
			if (p->pNext != NULL) {
				masvDKLTC += ",";
			}
		}
		fileOut << endl << ds[i].MALOPTC << "," << ds[i].MAMH << ","
			<< ds[i].NIEN_KHOA << "," << ds[i].HOC_KY << "," << ds[i].NHOM << "," << ds[i].sv_max << "," << ds[i].sv_min
			<< ",[" << masvDKLTC << "]" << "\n";
	}

	fileOut.close();
}
void InsertNodeIntoTree(TREE& tree, Lop_Tin_Chi* data);

void ReadListLopTinChi(TREE& t, DS_SINH_VIEN& ds_sv_original) {
	ifstream fileIn;
	ReadFileSinhVien(ds_sv_original);
	fileIn.open("DS_LOP_TIN_CHI.txt", ios::in);
	if (fileIn.fail())
	{
		cout << "Open file (DS_LOP_TIN_CHI.txt) failed. Please check and update path of file again !!!" << endl;
		return;
	};


	while (!fileIn.eof())
	{
		char s[1];
		Lop_Tin_Chi* data = new Lop_Tin_Chi;
		/*fileOut << endl << ds[i].MALOPTC << "," << ds[i].MAMH << ","
			<< ds[i].NIEN_KHOA << "," << ds[i].HOC_KY << "," << ds[i].NHOM  << "," << ds[i].sv_max << "," << ds[i].sv_min
			<< ",[" << "MSV123" << "," << "MSV234" << "]" << "\n";*/
		fileIn >> data->MALOPTC;
		fileIn.ignore(1);
		fileIn.getline(data->MAMH, MAX_MAMH, ',');
		fileIn.getline(data->NIEN_KHOA, MAX_NIENKHOA, ',');
		fileIn >> data->HOC_KY;
		fileIn.ignore(1);
		fileIn >> data->NHOM;
		fileIn.ignore(1);
		fileIn >> data->sv_max;
		fileIn.ignore(1);
		fileIn >> data->sv_min;
		fileIn.ignore(1);

		DS_SINH_VIEN* ds_sv = new DS_SINH_VIEN;
		ds_sv->pHead = NULL;
		ds_sv->pTail = NULL;
		ds_sv->totalSv = 0;
		data->ds_sv = ds_sv;
		int totalSv = 0;
		fileIn >> totalSv;
		char** massv = CreateArray(MAX_MASV, totalSv);
		char temp[1];
		fileIn.ignore(2);
		for (int i = 0; i < totalSv; i++)
		{
			if (i < totalSv - 1) {
				fileIn.getline(massv[i], MAX_MASV, ',');
			}
			else {
				fileIn.getline(massv[i], MAX_MASV, ']');
				fileIn.getline(temp, 1);
			}
			for (NODE_SINH_VIEN* p = ds_sv_original.pHead; p != NULL; p = p->pNext) {
				cout << p->data.TEN << endl;
				if (_strcmpi(massv[i], p->data.MASV) == 0) {
					NODE_SINH_VIEN* temp = p;
					InsertAndSortSvIntoDS(*ds_sv, temp);
					break;
				}
			}
			//cout << massv[i] << endl;
		}
		/*for (NODE_SINH_VIEN* p = ds_sv_original.pHead; p != NULL; p = p->pNext)
		{
			for (int i = 0; i < totalSv; i++)
			{
				if (_strcmpi(massv[i], p->data.MASV) == 0) {
					InsertAndSortSvIntoDS(*ds_sv, p);
				}
			}
		}*/
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
		cout << "Xoa thanh cong vi tri dau tien" << endl;
		system("pause");
		return;
	}
	if (_strcmpi(ds_sv.pTail->data.MASV, massv) == 0)
	{
		RemoveLast(ds_sv);
		cout << "Xoa thanh cong vi tri cuoi cung trong ds" << endl;
		system("pause");
		return;
	}
	bool exists = false;
	NODE_SINH_VIEN* g = new NODE_SINH_VIEN;
	for (NODE_SINH_VIEN* k = ds_sv.pHead; k != NULL; k = k->pNext)
	{
		if (_strcmpi(k->data.MASV, massv) == 0)
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
NODE_SINH_VIEN* Input_Sinh_Vien(DS_SINH_VIEN ds_sv)
{
	int slsv;
	char maLop[15];
	cout << "\nNhap ma lop: ";
	cin.getline(maLop, 15);
	NODE_SINH_VIEN* sv = new NODE_SINH_VIEN;
	if (sv == NULL)
	{
		cout << "Cap phat vung nho de khoi tao sv that bai." << endl;
		system("pause");
		return NULL;
	}
	cout << "\nNhap ho: ";
	cin.getline(sv->data.HO, 20);
	cout << "\nNhap ten: ";
	cin.getline(sv->data.TEN, 15);
	cout << "\nNhap gioi tinh: ";
	cin.getline(sv->data.PHAI, 4);
	do
	{
		cout << "\nNhap so dien thoai: ";
		cin.getline(sv->data.SDT, 25);
		if (!IsNumber(sv->data.SDT)) {
			cout << "Phone number invalid !";
			Sleep(2000);
			system("cls");
		}
	} while (!IsNumber(sv->data.SDT));
	cout << "\nNhap nam hoc: ";
	cin >> sv->data.NAMNHAPHOC;
	strcpy_s(sv->data.MALOP, 15, maLop);
	cin.ignore();
	strcpy_s(sv->data.MASV, 12, RandomID(ds_sv).c_str());
	sv->pNext = NULL;
	return sv;
}
bool UpdateSinhVien(DS_SINH_VIEN& ds_sv) {
	char masv[15];
	cout << "Nhap ma sv can xoa: "; cin.getline(masv, 15);
	bool exist = CheckExistMSSV(ds_sv, masv);
	if (!exist) {
		cout << "Sinh vien khong ton tai. Kiem tra lai!" << endl;
		return false;
	}
	char ho[20], ten[15], phai[4], sdt[25];
	int namnhaphoc;
	cout << "Nhap ho sinh vien:"; cin.getline(ho, 20);
	cout << "Nhap ten sinh vien:"; cin.getline(ten, 15);
	cout << "Nhap gioi tinh:"; cin.getline(phai, 4);
	cout << "Nhap so dien thoai sinh vien:"; cin.getline(sdt, 25);
	cout << "Nhap nam nhap hoc:"; cin >> namnhaphoc;
	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		if (_strcmpi(p->data.MASV, masv) == 0) {
			strcpy_s(p->data.HO, 20, ho);
			strcpy_s(p->data.TEN, 15, ten);
			strcpy_s(p->data.PHAI, 4, phai);
			strcpy_s(p->data.SDT, 25, sdt);
			p->data.NAMNHAPHOC = namnhaphoc;
			break;
		}
	}
	UpdateListStudentToFile(ds_sv);
	return true;
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
		p->data.ds_sv = data->ds_sv;
		p->data.HOC_KY = data->HOC_KY;
		p->data.MALOPTC = data->MALOPTC;
		strcpy_s(p->data.MAMH, 14, data->MAMH);
		p->data.NHOM = data->NHOM;
		strcpy_s(p->data.NIEN_KHOA, data->NIEN_KHOA);
		p->data.sv_max = data->sv_max;
		p->data.sv_min = data->sv_min;
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
	cout << "\nNhap ma mon hoc: "; cin.getline(p->MAMH, sizeof(p->MAMH));
	cout << "Nhap nien khoa: "; cin.getline(p->NIEN_KHOA, sizeof(p->NIEN_KHOA));
	cout << "Nhap hoc ky: "; cin >> p->HOC_KY;
	cout << "Nhap sl sinh vien max: "; cin >> p->sv_max;
	cout << "Nhap sl sinh vien min: "; cin >> p->sv_min;
	cout << "Nhap nhom:"; cin >> p->NHOM;
	cin.ignore();
	InsertNodeIntoTree(tree, p);
}
void ConvertTreeToArray(TREE t, Lop_Tin_Chi ds[], int& n) {
	if (t != NULL) {
		ds[n] = t->data;
		n++;
		ConvertTreeToArray(t->pLeft, ds, n);
		ConvertTreeToArray(t->pRight, ds, n);
	}
}
void ShowDSLopTinChi(Lop_Tin_Chi ds[], int n) {
	int total = 0;
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		cout << "\t====== LOP TIN CHI THU " << ++total << " ======" << endl;

		cout << "\nMa lop tin chi: " << ds[i].MALOPTC << endl;
		cout << "Ma mon hoc: " << ds[i].MAMH << endl;
		cout << "Nien khoa: " << ds[i].NIEN_KHOA << endl;
		cout << "Hoc ky: " << ds[i].HOC_KY << endl;
		cout << "Nhom: " << ds[i].NHOM << endl;
		cout << "So luong sinh vien toi da: " << ds[i].sv_max << endl;
		cout << "So luong sinh vien it nhat: " << ds[i].sv_min << endl;
		cout << "So luong sinh vien dang ky: " << ds[i].ds_sv->totalSv << endl;
		cout << "\t====== SINH VIEN THU " << ++k << " ======" << endl;
		for (NODE_SINH_VIEN* p = ds[i].ds_sv->pHead; p != NULL; p = p->pNext)
		{
			cout << "Ten sinh vien:" << p->data.HO << " " << p->data.TEN << endl;
			cout << "Ma lop: " << p->data.MALOP << endl;
			cout << "Ma sinh vien: " << p->data.MASV << endl;
			cout << "Nam nhap hoc: " << p->data.NAMNHAPHOC << endl;
			cout << "Phai: " << p->data.PHAI << endl;
			cout << "Sdt: " << p->data.SDT << endl;
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
void RemoveNodeOfTree(TREE& t, int ma) {
	if (t == NULL) return;
	if (t->data.MALOPTC > ma) {
		RemoveNodeOfTree(t->pLeft, ma);
	}
	else if (t->data.MALOPTC < ma) {
		RemoveNodeOfTree(t->pRight, ma);
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
// ===== END DS LOP TIN CHI =====

// MON HOC
void Insert_MonHoc(DS_MON_HOC& ds_mon_hoc)
{
	for (int i = 0; i < 2; i++)
	{
		MON_HOC* monhoc = new MON_HOC;
		strcpy_s(monhoc->MAMH, 11, RandomIDMH(ds_mon_hoc).c_str());
		cout << "\nNhap vao ten mon hoc:";
		cin.getline(monhoc->TENMH, 256);
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

// BEGIN DS DANG KY

void Init_DS_Dang_Ky(DS_DANG_KY& ds_dangky)
{
	ds_dangky.pHead = NULL;
	ds_dangky.pTail = NULL;
	ds_dangky.n = 0;
}

void InsertLastDSDKY(DS_DANG_KY& ds_dk, DANG_KY* dk)
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
	ds_dk.n++;
}

void Show_DS_Dang_Ky(DS_DANG_KY ds_dk) {
	for (DANG_KY* p = ds_dk.pHead; p != NULL; p = p->pNext) {
		cout << "Ma sv:" << p->MASV << endl;
		cout << "Diem:" << p->DIEM << endl;
	}
}

// END DS DANG KY

int main()
{
	//SetColor(bk_blue | red);
	//string a = openLogin();
	//if (a.length() > 0) {
		DrawMainLayout("");
		ProcessConrtol();
	//}
	srand(time(NULL));
	/*DS_DANG_KY ds_dangky;
	int n = 0;
	Init_DS_Dang_Ky(ds_dangky);
	ReadFileDS_DANG_KY(ds_dangky);
	Show_DS_Dang_Ky(ds_dangky);*/
	/*TREE tree;
	DS_SINH_VIEN ds_sv_original;
	Lop_Tin_Chi* ds = new Lop_Tin_Chi[100];
	int n = 0;
	InitTree(tree);
	ReadListLopTinChi(tree, ds_sv_original);*/
	//InsertLopTCIntoTree(tree);
	/*ConvertTreeToArray(tree, ds, n);
	ShowDSLopTinChi(ds, n);*/
	//UpdateListLopTinChiToFile(ds, n);
	//int x;
	//cout << "Nhap ma lop tin chi can xoa:"; cin >> x;
	//RemoveNodeOfTree(tree, x);
	//n = 0;
	//ConvertTreeToArray(tree, ds, n);
	//ShowDSLopTinChi(ds, n);

	//Show_DS_Sinh_Vien(ds_sv);
	//UpdateListLopTinChiToFile(ds, n);
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
	//system("pause");
	return 0;
}