#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>;
#include <string>;
#include <fstream>;
#include <ctime>;
#include "console.h";

#define MAX_MON_HOC 300
#define MAX_MAMH 11
#define MAX_TENMH 100
#define MAX_MASV 13
#define MAX_PHAI 4
#define MAX_SDT 11
#define MAX_MALOP 16
#define MAX_HO 20
#define MAX_TEN 15
#define MAX_NIENKHOA 10

#define bk_blue 0x0030
#define red 0x0004



using namespace std;


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

// ===== BEGIN DS SV DANG KY =====
struct sv_dang_ky
{
	// data
	char MASV[MAX_MASV];
	float DIEM;
	// pointer
	sv_dang_ky* pNext;
};
typedef struct sv_dang_ky SV_DANG_KY;
struct ds_dang_ky
{
	SV_DANG_KY* pHead = NULL;
	SV_DANG_KY* pTail = NULL;
	int n;
};
typedef struct ds_dang_ky DS_SV_DANG_KY;
// ===== END DS SV DANG KY =====



static string mainActions[4] = { "CHUC NANG LOP TIN CHI",
"CHUC NANG SINH VIEN", "CHUC NANG MON HOC", "CHUC NANG DIEM" };

static string propertySinhVien[7] = {
	"Ma Sinh Vien", "Ma Lop", "Ho SV", "Ten SV", "Phai", "So Dien Thoai", "Nam Nhap Hoc"
};

static string nameAction = "";



struct MenuItem {
	RECT rect;
	std::string name;
};
struct MenuContent {
	MenuItem* menus = NULL;
	int n = 0;
	int posStatus = 0;
};
static MenuContent MenuFeatures = {
	new MenuItem[4] {
	{{3,3,20,2},"Lop Tin Chi"},
	{{3,6,20,2},"SinhVien"},
	{{3,9,20,2},"Mon Hoc"},
	{{3,12,20,2},"Diem"}
	},
	 4
};

static MenuContent MenuMonHoc = {
	new MenuItem[3] {
		{{3,18,20,2},"In danh sach MH"},
		{{3,21,20,2},"Xoa or Sua (MH)"},
		{{3,24,20,2},"Them MH"}
	},
	 3
};
static MenuContent MenuSinhVien = {
	new MenuItem[3] {
		{{3,18,20,2},"In danh sach SV"},
		{{3,21,20,2},"Xoa or Sua (SV)"},
		{{3,24,20,2},"Nhap DS Sinh Vien"},
	},
	 3
};

static MenuContent MenuLopTinChi = {
	new MenuItem[3] {
	{{3,18,20,2},"In danh sach TC"},
	{{3,21,20,2},"Xoa or Sua (TC)"},
	{{3,24,20,2},"Them Lop TC"},
	},
	 3
};
static MenuContent MenuDiem = {
	new MenuItem[2] {
	{{3,18,20,2},"Nhap diem"},
	{{3,21,20,2},"Xem diem"},
	},
	 2
};

static MenuContent ActionQuit = {
	new MenuItem[2] {
		{{55, 12, 10, 2},"Ok"},
	{{68, 12, 10, 2},"Cancel"},
	},
	 2
};



struct AppContext {
	AppContext() {
		tree = NULL;
		nLTC = 0;
		ds_mh.n = 0;
		ds_sv_original.totalSv = 0;
	}
	TREE tree;
	DS_SINH_VIEN ds_sv_original;
	Lop_Tin_Chi* ds[100];
	int nLTC;
	DS_MON_HOC ds_mh;
};


// ===== BEGIN HELPER =====
bool CheckExistMSSV(DS_SINH_VIEN ds_sv, char* massv);
bool CheckExistMaMH(DS_MON_HOC ds_mh, char* maMH);
bool CheckExistMaLTC(TREE tree, int maLopTc);
void Trim(string& str);
string RandomID(DS_SINH_VIEN ds_sv);
string RandomIDMH(DS_MON_HOC ds_mon_hoc);
int RandomIDLTC(TREE tree);
bool IsNumber(char* s);
bool CheckExistLop(char* malop);
void InsertLopIntoDSLop(string lop);
char** CreateArray(int x, int y);
SINH_VIEN** CreateArraySV(int x, int y);
bool CheckInputBoxIsNull(string str[], int n);
// ===== END HELPER =====

// HANDLE FILES
void Read_File_MonHoc(DS_MON_HOC& ds_mon_hoc);
void UpdateFileDSMonHoc(DS_MON_HOC ds_mh);
void UpdateListStudentToFile(DS_SINH_VIEN& ds_sv);
void InsertLastSv(DS_SINH_VIEN& ds_sv, NODE_SINH_VIEN* nodeSV);
void InsertFirstSv(DS_SINH_VIEN& ds_sv, NODE_SINH_VIEN* nodeSV);
void InsertAndSortSvIntoDS(DS_SINH_VIEN& ds_sv, NODE_SINH_VIEN* nodeSV);
void ReadFileSinhVien(DS_SINH_VIEN& ds_sv);

// DANH SACH DANG KY
void InsertLastDSDKY(DS_SV_DANG_KY& ds_dk, SV_DANG_KY* dk);
void ReadFileDS_DANG_KY(DS_SV_DANG_KY& ds_dk);

// END DANH SACH DANG KY

// TODO:
void UpdateListSvToLopTC(Lop_Tin_Chi*& ds, int totalLopTc, DS_SINH_VIEN& ds_sv_original, char* masvDKLTC[]);
void UpdateListLopTinChiToFile(Lop_Tin_Chi* ds[], int n);
void InsertNodeIntoTree(TREE& tree, Lop_Tin_Chi* data);
void ReadListLopTinChi(TREE& t, DS_SINH_VIEN& ds_sv_original);
// END HANDLE FILES

// SINH VIEN
void Init_DS_Sinh_Vien(DS_SINH_VIEN& ds);
bool isEmptyDSSV(DS_SINH_VIEN ds_sv);
void RemoveFirst(DS_SINH_VIEN& ds_sv);
void RemoveLast(DS_SINH_VIEN& ds_sv);
void RemoveSvByMSSV(DS_SINH_VIEN& ds_sv, char* massv);
NODE_SINH_VIEN* Input_Sinh_Vien(DS_SINH_VIEN ds_sv);
bool UpdateSinhVien(DS_SINH_VIEN& ds_sv);
void Show_DS_Sinh_Vien(DS_SINH_VIEN ds_sv);
void ConvertLinkedListSV(DS_SINH_VIEN ds_sv, SINH_VIEN* dsSV[]);
//  END SINH VIEN

// ===== BEGIN DS LOP TIN CHI =====
void InitTree(TREE& tree);
void InsertNodeIntoTree(TREE& tree, Lop_Tin_Chi* data);
NODE_LOP_TIN_CHI* TravelTree(TREE t, int maLop);
void InsertLopTCIntoTree(TREE& tree);
void ConvertTreeToArray(TREE t, Lop_Tin_Chi* ds[], int& n);
void ShowDSLopTinChi(Lop_Tin_Chi* ds[], int n);
void Node_The_Mang(TREE& t, TREE& x);
void RemoveNodeOfTree(TREE& t, int ma);
void UpdateNodeOfTree(TREE& t, Lop_Tin_Chi* data);
Lop_Tin_Chi* InputUpdateTree();
void ShowDSSVDangKyLTC(Lop_Tin_Chi* ds[], int n);
bool CheckLopTinChiToInsert(Lop_Tin_Chi* ds[], int n, Lop_Tin_Chi* data);
// ===== END DS LOP TIN CHI =====

// MON HOC
void Insert_MonHoc(DS_MON_HOC& ds_mon_hoc);
void RemoveMonHoc(DS_MON_HOC& ds_mon_hoc, char* maMH);
void Show_DS_MonHoc(DS_MON_HOC dsMonHoc);
// END MON HOC

// BEGIN DS DANG KY
void Init_DS_Dang_Ky(DS_SV_DANG_KY& ds_dangky);
void InsertLastDSDKY(DS_SV_DANG_KY& ds_dk, SV_DANG_KY* dk);
void Show_DS_Dang_Ky(DS_SV_DANG_KY ds_dk);

void CommonShowSvList(AppContext context);
// END DS DANG KY
void InDanhSachLopTinChi(Lop_Tin_Chi* ltc[], int n, int x, int y);
void InDanhSachSinhVien(SINH_VIEN* ds_sv[], int n, int x, int y);
void InDanhSachMonHoc(DS_MON_HOC ds_mh, int n, int x, int y);



#endif // !STRUCTURE_H
