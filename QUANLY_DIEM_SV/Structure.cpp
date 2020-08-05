
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

SINH_VIEN** CreateArraySV(int x, int y) {
	SINH_VIEN** sv = new SINH_VIEN * [y];
	for (int i = 0; i < y; i++)
	{
		sv[i] = new SINH_VIEN[x];
	}
	return sv;
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
void UpdateListLopTinChiToFile(Lop_Tin_Chi* ds[], int n) {
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
		if (ds[i]->ds_sv != NULL && ds[i]->ds_sv->totalSv != 0) {

			string masvDKLTC;
			for (NODE_SINH_VIEN* p = ds[i]->ds_sv->pHead; p != NULL; p = p->pNext) {
				masvDKLTC += (string)p->data.MASV;
				if (p->pNext != NULL) {
					masvDKLTC += ",";
				}
			}
			fileOut << ds[i]->MAMH << "," << ds[i]->NIEN_KHOA
				<< "," << ds[i]->MALOPTC << "," << ds[i]->HOC_KY << "," << ds[i]->NHOM << "," << ds[i]->sv_max << ","
				<< ds[i]->sv_min << "," << ds[i]->ds_sv->totalSv << ",[" << masvDKLTC << "]" << endl;
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
void ReadListLopTinChi(TREE& t, DS_SINH_VIEN& ds_sv_original) {
	ifstream fileIn;
	ReadFileSinhVien(ds_sv_original);
	fileIn.open("DS_LOP_TIN_CHI.txt", ios::in);
	if (fileIn.fail())
	{
		cout << "Open file (DS_LOP_TIN_CHI.txt) failed. Please check and update path of file again !!!" << endl;
		return;
	};


	while (fileIn.peek() != EOF)
	{
		char s[1];
		Lop_Tin_Chi* data = new Lop_Tin_Chi;
		/*fileOut << endl << ds[i]->MALOPTC << "," << ds[i]->MAMH << ","
			<< ds[i]->NIEN_KHOA << "," << ds[i]->HOC_KY << "," << ds[i]->NHOM  << "," << ds[i]->sv_max << "," << ds[i]->sv_min
			<< ",[" << "MSV123" << "," << "MSV234" << "]" << "\n";*/
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

		DS_SINH_VIEN* ds_sv = new DS_SINH_VIEN;
		ds_sv->pHead = NULL;
		ds_sv->pTail = NULL;
		ds_sv->totalSv = 0;
		data->ds_sv = ds_sv;
		int totalSv = 0;
		fileIn >> totalSv;

		if (totalSv > 0) {
			char** massv = CreateArray(MAX_MASV, totalSv);
			//char temp[1];
			fileIn.ignore(2);
			for (int i = 0; i < totalSv; i++)
			{
				if (i < totalSv - 1) {
					fileIn.getline(massv[i], MAX_MASV, ',');
				}
				else {
					fileIn.getline(massv[i], MAX_MASV, ']');
					//fileIn.getline(temp, 1);
				}
				for (NODE_SINH_VIEN* p = ds_sv_original.pHead; p != NULL; p = p->pNext) {
					if (_strcmpi(massv[i], p->data.MASV) == 0) {
						NODE_SINH_VIEN* temp = new NODE_SINH_VIEN;
						temp->data = p->data;
						InsertAndSortSvIntoDS(*ds_sv, temp);
						break;
					}
				}
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
bool UpdateSinhVien(DS_SINH_VIEN& ds_sv) {
	char masv[MAX_MASV];
	cout << "Nhap ma sv can xoa: "; cin.getline(masv, MAX_MASV);
	bool exist = CheckExistMSSV(ds_sv, masv);
	if (!exist) {
		cout << "Sinh vien khong ton tai. Kiem tra lai!" << endl;
		return false;
	}
	char ho[MAX_HO], ten[MAX_TEN], phai[MAX_PHAI], sdt[MAX_SDT];
	int namnhaphoc;
	cout << "Nhap ho sinh vien:"; cin.getline(ho, MAX_HO);
	cout << "Nhap ten sinh vien:"; cin.getline(ten, MAX_TEN);
	cout << "Nhap gioi tinh:"; cin.getline(phai, MAX_PHAI);
	cout << "Nhap so dien thoai sinh vien:"; cin.getline(sdt, MAX_SDT);
	cout << "Nhap nam nhap hoc:"; cin >> namnhaphoc;
	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		if (_strcmpi(p->data.MASV, masv) == 0) {
			strcpy_s(p->data.HO, MAX_HO, ho);
			strcpy_s(p->data.TEN, MAX_TEN, ten);
			strcpy_s(p->data.PHAI, MAX_PHAI, phai);
			strcpy_s(p->data.SDT, MAX_SDT, sdt);
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
		strcpy_s(p->data.MAMH, MAX_MAMH, data->MAMH);
		p->data.NHOM = data->NHOM;
		strcpy_s(p->data.NIEN_KHOA, MAX_NIENKHOA, data->NIEN_KHOA);
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
	cout << "\nNhap ma mon hoc: "; cin.getline(p->MAMH, MAX_MAMH);
	cout << "Nhap nien khoa: "; cin.getline(p->NIEN_KHOA, MAX_NIENKHOA);
	cout << "Nhap hoc ky: "; cin >> p->HOC_KY;
	cout << "Nhap sl sinh vien max: "; cin >> p->sv_max;
	cout << "Nhap sl sinh vien min: "; cin >> p->sv_min;
	cout << "Nhap nhom:"; cin >> p->NHOM;
	p->ds_sv = NULL;
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
void ShowDSLopTinChi(Lop_Tin_Chi* ds[], int n) {
	int total = 0;
	for (int i = 0; i < n; i++)
	{
		cout << "\t====== LOP TIN CHI THU " << ++total << " ======" << endl;

		cout << "\nMa lop tin chi: " << ds[i]->MALOPTC << endl;
		cout << "Ma mon hoc: " << ds[i]->MAMH << endl;
		cout << "Nien khoa: " << ds[i]->NIEN_KHOA << endl;
		cout << "Hoc ky: " << ds[i]->HOC_KY << endl;
		cout << "Nhom: " << ds[i]->NHOM << endl;
		cout << "So luong sinh vien toi da: " << ds[i]->sv_max << endl;
		cout << "So luong sinh vien it nhat: " << ds[i]->sv_min << endl;
		if (ds[i]->ds_sv != NULL) {
			int k = 0;
			cout << "So luong sinh vien dang ky: " << ds[i]->ds_sv->totalSv << endl;
			for (NODE_SINH_VIEN* p = ds[i]->ds_sv->pHead; p != NULL; p = p->pNext)
			{
				cout << "\t====== SINH VIEN THU " << ++k << " ======" << endl;
				cout << "Ten sinh vien:" << p->data.HO << " " << p->data.TEN << endl;
				cout << "Ma lop: " << p->data.MALOP << endl;
				cout << "Ma sinh vien: " << p->data.MASV << endl;
				cout << "Nam nhap hoc: " << p->data.NAMNHAPHOC << endl;
				cout << "Phai: " << p->data.PHAI << endl;
				cout << "Sdt: " << p->data.SDT << endl;
			}
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
void ShowDSSVDangKyLTC(Lop_Tin_Chi* ds[], int n) {
	char nienKhoa[MAX_NIENKHOA];
	char maMonHoc[MAX_MAMH];
	int nhom, hocKy;
	bool exist = true;
	cout << "\nNhap nien khoa:"; cin.getline(nienKhoa, MAX_NIENKHOA);
	cout << "Nhap ma mon hoc:";  cin.getline(maMonHoc, MAX_MAMH);
	cout << "Nhap nhom:"; cin >> nhom;
	cout << "Nhap hoc ky:"; cin >> hocKy;

	for (int i = 0; i < n; i++) {
		if (ds[i]->HOC_KY == hocKy && ds[i]->NHOM == nhom
			&& _strcmpi(ds[i]->NIEN_KHOA, nienKhoa) == 0
			&& _strcmpi(ds[i]->MAMH, maMonHoc) == 0) {
			if (ds[i]->ds_sv == NULL) {
				exist = false;
				break;
			}
			for (NODE_SINH_VIEN* p = ds[i]->ds_sv->pHead; p != NULL; p = p->pNext) {
				cout << "Ho ten:" << p->data.HO << " " << p->data.TEN << endl;
			}
		}
	}
}
bool CheckLopTinChiToInsert(Lop_Tin_Chi* ds[], int n, Lop_Tin_Chi* data) {
	bool exist = false;
	int i = 0;
	while (i < n)
	{
		if (_strcmpi(ds[i]->MAMH, data->MAMH) == 0
			&& _strcmpi(ds[i]->NIEN_KHOA, data->NIEN_KHOA) == 0
			&& ds[i]->HOC_KY == data->HOC_KY && ds[i]->NHOM == data->NHOM) {
			exist = true;
			break;
		}
		++i;
	}
	return exist;
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
void Init_DS_Dang_Ky(DS_SV_DANG_KY& ds_dk)
{
	ds_dk.pHead = NULL;
	ds_dk.pTail = NULL;
	ds_dk.n = 0;
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
	ds_dk.n++;
}
void Show_DS_Dang_Ky(DS_SV_DANG_KY ds_dk) {
	for (SV_DANG_KY* p = ds_dk.pHead; p != NULL; p = p->pNext) {
		cout << "Ma sv:" << p->MASV << endl;
		cout << "Diem:" << p->DIEM << endl;
	}
}
void ShowSingleLTC(Lop_Tin_Chi* ltc, int index) {
	cout << setw(3) << index + 1 << char(179) << setw(10) << ltc->MALOPTC
		<< char(179) << setw(11) << ltc->MAMH << char(179)
		<< setw(4) << ltc->NHOM << char(179) << setw(20)
		<< ltc->NIEN_KHOA << char(179)
		<< setw(7) << ltc->sv_max << char(179)
		<< setw(7) << ltc->sv_min << char(179)
		<< setw(7) << ltc->sv_max - ltc->ds_sv->totalSv << char(179);
}void ShowSingleSV(SINH_VIEN* sv, int index) {
	cout << setw(3) << index + 1 << char(179) << setw(15) << sv->MALOP << char(179)
		<< setw(13) << sv->MASV << char(179)
		<< setw(20) << sv->HO << char(179) << setw(15) << sv->TEN << char(179)
		<< setw(5) << sv->PHAI << char(179) << setw(11) << sv->SDT << char(179);
}
void ShowSingleMonHoc(MON_HOC* mh, int index) {
	cout << setw(3) << index + 1 << char(179) << setw(15) << mh->MAMH << char(179)
		<< setw(30) << mh->TENMH << char(179)
		<< setw(15) << mh->STCLT << char(179) << setw(15) << mh->STCTH << char(179);
}
// END DS DANG KY
void CommonShowSvList(AppContext context) {
	int total = context.ds_sv_original.totalSv;
	SINH_VIEN** ds_sv = CreateArraySV(total, sizeof(SINH_VIEN));
	ConvertLinkedListSV(context.ds_sv_original, ds_sv);
	InDanhSachSinhVien(ds_sv, total, 40, 10);
}


void InDanhSachMonHoc(DS_MON_HOC ds_mh, int n, int x, int y) {
	cout << setfill(' ');

	SetColor(color_black | colorbk_white);
	gotoXY(x, y);
	cout << setw(3) << "STT" << char(179) << setw(15) << "MaMH" << char(179) << setw(30) << "Ten MH" << char(179)
		<< setw(15) << "So tin chi LT" << char(179) << setw(15) << "So tin chi TH" << char(179);

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
		case 1060: {

			//todo ::


			goto paint;
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
			if (posActive < perPage - 1 && posActive + posPrint < n - 1) {
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
				   ShowSingleMonHoc(ds_mh.ds[indexitem], indexitem);
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
				   int index = posActive + posPrint;
				   ShowSingleMonHoc(ds_mh.ds[index], index);
			   }
			   break;
		}
		}
		key = inputKey();
	} while (key != key_esc);
	clrscr(30, 10, 90, 10, ' ');
}
void InDanhSachLopTinChi(Lop_Tin_Chi* ltc[], int n, int x, int y) {
	cout << setfill(' ');

	SetColor(color_black | colorbk_white);
	gotoXY(x, y);
	cout << setw(3) << "STT" << char(179) << setw(10) << "MaLopTC" << char(179) << setw(11) << "MaMH" << char(179)
		<< setw(4) << "NHOM" << char(179) << setw(20) << "NIEN KHOA" << char(179)
		<< setw(7) << "SV MAX" << char(179) << setw(7) << "SV MIN" << char(179) << setw(7) << "CON LAI" << char(179);

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
		case 1060: {

			//todo ::


			goto paint;
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
	clrscr(30, 10, 90, 10, ' ');

}
void InDanhSachSinhVien(SINH_VIEN* ds_sv[], int n, int x, int y) {
	cout << setfill(' ');

	SetColor(color_black | colorbk_white);
	gotoXY(x, y);
	cout << setw(3) << "STT" << char(179) << setw(15) << "Ma Lop" << char(179) << setw(13) << "Ma SV" << char(179)
		<< setw(20) << "Ho" << char(179) << setw(15) << "Ten" << char(179)
		<< setw(5) << "Phai" << char(179) << setw(11) << "SDT" << char(179);

	int currentPage = 0, posActive = -1;
	int posPrint = 0;
	int perPage = 10;
	int totalPage = n / perPage;

	if (n % perPage != 0) {
		totalPage += 1;
	}

	int key = -1;

	perPage = perPage > n ? n : perPage;
	do {
		switch (key)
		{
		case 1060: {

			//todo ::


			goto paint;
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
	clrscr(40, 10, 90, 15, ' ');
}
#endif // !STRUCTURE_CPP
