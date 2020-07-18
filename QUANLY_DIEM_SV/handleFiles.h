#pragma once
#include <string.h>;

using namespace std;
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
void WriteFileSinhVien(SINH_VIEN* sv) {
	ofstream fileOut;
	fileOut.open("C:\\Users\\Nguyen Dai\\source\\repos\\QLDIEMSV_HTC\\QLDIEMSV_HTC\\DS_SINH_VIEN.txt", ios_base::out);
	if (fileOut.fail())
	{
		cout << "Open file (DS_SINH_VIEN.txt) to write failed. Please check and update path of file again !!!" << endl;
		return;
	};
	cout << sv->HO << " " << sv->TEN;
	fileOut.close();
}

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