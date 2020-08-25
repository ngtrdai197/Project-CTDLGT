#ifndef MENU_H
#define MENU_H

#include "Structure.h"


int openLogin(AppContext& context) {
	rectagle(50, 10, 50, 15);
	gotoXY(55, 13);
	cout << "Username";
	rectagle(55, 14, 25, 2); // width of input

	gotoXY(55, 18);
	cout << "Password";
	rectagle(55, 19, 25, 2);
	gotoXY(57, 15);

	string auth[2];
	int pos = 0;
	int key = -1;
	do {
		key = inputKey();
		switch (key)
		{
		case key_esc: {
			/*MenuContent* menuCurrent = &MenuFeatures;
			menuCurrent = &ActionConfirm;
			SetColor(colorbk_green);
			ConfirmDialog("Xac nhan dang xuat ?");
			key = ControlMenu(menuCurrent, 7, 12);
			if (key == key_Enter && menuCurrent->posStatus == 0) {
				return -1;
			}
			else {
				return -2;
			}*/
			break;
		}
		case key_Up: {
			pos = 0;
			gotoXY(57 + auth[pos].length(), 15);
			break;
		}
		case key_Down: {
			pos = 1;
			gotoXY(57 + auth[pos].length(), 20);
			break;
		};
		case key_tab: {
			pos = (pos + 1) % 2;
			if (pos == 0) {
				gotoXY(57 + auth[pos].length(), 15);
			}
			else {
				gotoXY(57 + auth[pos].length(), 20);
			}
			break;
		}
		case key_bkspace: {
			if (auth[pos].length() < 1) break;

			cout << "\b \b";
			auth[pos].erase(auth[pos].length() - 1, 1);
			break;
		}
		case key_Enter: {
			char clone[MAX_MASV];
			strcpy_s(clone, MAX_MASV, auth[0].c_str());
			if (auth[0] == "GV" && auth[1] == "123") {
				strcpy_s(context.currentUser, MAX_MASV, "Giang Vien");
				return 0;
			}
			if (CheckExistMSSV(context.ds_sv, clone) && auth[1] == "123") {
				strcpy_s(context.currentUser, MAX_MASV, GetSinhVien(context.ds_sv, clone)->data.MASV);
				return 1;
			}
			else {
				gotoXY(57, 24);
				cout << "Thong tin dang nhap khong dung!";
				gotoXY(57 + auth[pos].length(), pos == 0 ? 15 : 20);
				break;
			}
		}
		default:
			if (key > 31 && key < 127) {
				if (pos == 0) {
					gotoXY(57 + auth[pos].length(), 15);
				}
				else {
					gotoXY(57 + auth[pos].length(), 20);
				}
				if (pos == 0 && auth[pos].length() <= MAX_MASV) {
					key = toupper(key);
					auth[pos] += key;
					cout << char(key);
				}
				else if (pos == 1 && auth[pos].length() < 20) {
					auth[pos] += key;
					cout << "*";
				}
			}
			break;
		}
	} while (key != key_esc);
	return -1;
}

void ShowGuide() {
	gotoXY(3, 33);
	cout << char(24) << " Di chuyen len";
	gotoXY(3, 35);
	cout << char(25) << " Di chuyen xuong";
	gotoXY(3, 37);
	cout << "Enter de chon";
	gotoXY(3, 39);
	cout << "ESC de thoat";
}

void DrawContentLopTC() {
	rectagle(28, 10, 6, 2); // show currently pointer
	gotoXY(29, 11);
	cout << "STT";
	rectagle(34, 10, 12, 2); // ma lop
	gotoXY(35, 11);
	cout << "Ma lop TC";
	rectagle(46, 10, 12, 2); // ma mon hoc
	gotoXY(47, 11);
	cout << "Ma mon hoc";
	rectagle(58, 10, 25, 2); // ten mon hoc
	gotoXY(59, 11);
	cout << "Ten mon hoc";
	rectagle(83, 10, 10, 2); // nien khoa
	gotoXY(84, 11);
	cout << "N-Khoa";
	rectagle(93, 10, 9, 2); // hoc ky
	gotoXY(94, 11);
	cout << "Hoc ky";
	rectagle(102, 10, 9, 2); // nhom
	gotoXY(103, 11);
	cout << "Nhom";
	rectagle(111, 10, 8, 2); // sv max
	gotoXY(112, 11);
	cout << "Max sv";
	rectagle(119, 10, 8, 2); // sv min
	gotoXY(120, 11);
	cout << "Min sv";
	rectagle(127, 10, 12, 2); // so luong con lai
	gotoXY(128, 11);
	cout << "SL con lai";
}
void DrawContentMonHoc() {
	rectagle(28, 10, 6, 2);
	gotoXY(29, 11);
	cout << "STT";

	rectagle(34, 10, 12, 2); // ma mon hoc
	gotoXY(35, 11);
	cout << "Ma mon hoc";

	rectagle(46, 10, 35, 2); // ten mon hoc
	gotoXY(47, 11);
	cout << "Ten mon hoc";

	rectagle(81, 10, 15, 2); // so tin chi ly thuyet
	gotoXY(82, 11);
	cout << "So tin LT";

	rectagle(96, 10, 15, 2); // so tin chi ly thuyet
	gotoXY(97, 11);
	cout << "So tin TH";
}
char DrawFormInput(int x, int y, int width, string Texts[], int maxText[], int n) {

	int offset = 3;

	for (int i = 0; i < n; i++)
	{
		// index > 2 enter number else enter string
		InputBox(Texts[i], x, y + (i * offset), width, maxText[i], true, i < 2 ? true : false, false, false);
	}

	int indexCurrent = 0;
	int key = -1;

	do
	{
		key = InputBox(Texts[indexCurrent], x, y + (indexCurrent * offset),
			width, maxText[indexCurrent], false, indexCurrent < 2 ? true : false, false, false);
		if (key == key_tab) {
			indexCurrent = (indexCurrent + 1) % n;
		}

	} while (key != key_esc && key != key_Enter);
	return key;
}
char DrawFormInputDiem(int x, int y, int width, string Texts[], int maxText[]) {

	SetColor(color_black | colorbk_green);
	gotoXY(63, y + 2);
	cout << "Diem SV: ";
	InputBox(Texts[0], x, y + 1, width, maxText[0], true, false, false, true);
	int key = -1;

	do
	{
		key = InputBox(Texts[0], x, y + 1, width, maxText[0], false, false, false, true);
	} while (key != key_esc && key != key_Enter);
	return key;
}

int ProcessControlGV(AppContext& context) {

	MenuContent* menuCurrent = &MenuFeatures;

	do {
		int key = ControlMenu(menuCurrent, color_darkwhite, color_green);

		if (menuCurrent == &MenuFeatures) {
			if (key == key_Enter)
				switch (menuCurrent->posStatus)
				{
				case 0://menu lop  tin chi
				{
					menuCurrent = &MenuLopTinChi;
					break;
				}
				case 1: {
					menuCurrent = &MenuSinhVien;
					break;
				}
				case 2: {
					menuCurrent = &MenuMonHoc;
					break;
				}
				case 3: {
					// Display / Update Score of students
					do
					{
						key = Search_GV_LTCByConditions(context, menuCurrent->posStatus, true);
					} while (key != key_esc);
					break;
				}
				default:
					break;
				}
			else if (key == key_esc) {
				menuCurrent = &ActionConfirm;
				ConfirmDialog("Xac nhan dang xuat ?");
				key = ControlMenu(menuCurrent, 7, 12);
				if (key == key_Enter && menuCurrent->posStatus == 0) {
					return key;
				}
				else {
					menuCurrent = &MenuFeatures;
					clrscr(50, 5, 40, 14, ' ');
				}
			}
		}
		else if (menuCurrent == &MenuLopTinChi) {
			if (key == key_esc) {
				menuCurrent = &MenuFeatures;
				clrscr(3, 18, 20, 3 * menuCurrent->n, ' ');
			}
			else {
				switch (menuCurrent->posStatus) {
				case 0: {
					if (key == key_Enter) {
						SetColor(color_darkwhite);
						context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
						context.nLTC = 0;
						ConvertTreeToArray(context.tree, context.ds, context.nLTC);
						InDanhSachLopTinChi(context, context.ds, context.nLTC, 40, 10, menuCurrent->posStatus, false, false);
					}
					break;
				}
				case 1: {
					SetColor(color_darkwhite);
					int keyRemove = -1;
					gotoXY(40, 3);
					cout << "F2: Xoa LTC - F3: Sua LTC - ESC: Thoat";
					do
					{
						context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
						context.nLTC = 0;
						ConvertTreeToArray(context.tree, context.ds, context.nLTC);
						keyRemove = InDanhSachLopTinChi(context, context.ds, context.nLTC, 40, 10, menuCurrent->posStatus, false, false);
					} while (keyRemove != key_esc);
					break;
				}
				case 2: {
					string Texts[6] = { "" };
					int maxTexts[6] = { MAX_MAMH - 1, MAX_NIENKHOA - 1,3,3,3,3 };
					int key = -1;
					SetColor(color_darkwhite);
					do
					{
						SetColor(color_white | colorbk_green);
						rectagle(45, 5, 65, 22);
						SetColor(color_white);
						key = DrawFormInputLTC(70, 6, 30, Texts, maxTexts, 6, false);
						if (key == key_Enter) {
							if (!CheckInputBoxIsNull(Texts, 6)) {
								// validate data
								Lop_Tin_Chi* p = new Lop_Tin_Chi;
								strcpy_s(p->MAMH, MAX_MAMH, Texts[0].c_str());
								strcpy_s(p->NIEN_KHOA, MAX_NIENKHOA, Texts[1].c_str());
								p->HOC_KY = stoi(Texts[2]);
								p->NHOM = stoi(Texts[3]);
								p->sv_max = stoi(Texts[4]);
								p->sv_min = stoi(Texts[5]);
								p->ds_sv_dky.pHead = NULL;
								if (CheckExistMaMH(context.ds_mh, p->MAMH)) {
									context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
									context.nLTC = 0;
									ConvertTreeToArray(context.tree, context.ds, context.nLTC);
									bool exist = CheckLopTinChiToInsert(context.ds, context.nLTC, p);
									p->MALOPTC = RandomIDLTC(context.ds, context.nLTC);

									if (!exist) {
										if (p->sv_min <= 0 || p->sv_min > p->sv_max) {
											gotoXY(60, 25);
											SetColor(color_red);
											string a = "SV min > 0, va < SV max. Kiem tra lai!";
											cout << a;
											Sleep(1500);
										}
										else if (CheckNienKhoa_InValid(Texts[1])) {
											gotoXY(50, 25);
											SetColor(color_red);
											string a = "Nien khoa khong hop le (>= 2000 & <=2050). Ex: 2015-2020";
											cout << a;
											Sleep(1500);
										}
										else {
											InsertNodeIntoTree(context.tree, p);
											context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
											context.nLTC = 0;
											ConvertTreeToArray(context.tree, context.ds, context.nLTC);
											UpdateListLopTinChiToFile(context.ds, context.nLTC);
											delete p;
											for (int i = 0; i < 6; i++)
											{
												Texts[i].clear();
											}
											gotoXY(60, 25);
											SetColor(color_red);
											string a = "Them lop tin chi thanh cong !";
											cout << a;
											Sleep(1500);
										}
									}
									else {
										gotoXY(60, 25);
										SetColor(color_red);
										string a = "Thong tin lop tin chi da ton tai. Kiem tra lai !";
										cout << a;
										Sleep(1500);
									}
								}
								else {
									gotoXY(60, 25);
									SetColor(color_red);
									string a = "Ma mon hoc khong ton tai. Kiem tra lai !";
									cout << a;
									Sleep(1500);
								}
							}
							else {
								gotoXY(60, 25);
								SetColor(color_red);
								string a = "Du lieu nhap khong duoc de trong!";
								cout << a;
								Sleep(1500);
							}
						}
					} while (key != key_esc);
					clrscr(40, 5, 90, 35, ' ');
					break;
				}
				case 3: {
					// Show list sv by conditions
					do
					{
						key = Search_GV_LTCByConditions(context, menuCurrent->posStatus, false);
					} while (key != key_esc);
					break;
				}
				default:
					break;
				}
			}
		}
		else if (menuCurrent == &MenuSinhVien) {
			if (key == key_esc) {
				menuCurrent = &MenuFeatures;
				clrscr(3, 18, 20, 3 * menuCurrent->n, ' ');
			}
			else {
				switch (menuCurrent->posStatus) {
				case 0: {
					if (key == key_Enter) {
						SetColor(color_darkwhite);
						string maLop = "";
						int key = -1;
						char cloned[MAX_MALOP];
						bool exist = false;
						do
						{
							SetColor(color_darkwhite | colorbk_black);
							key = DrawFormInputLop(60, 5, 30, maLop, MAX_MALOP - 1);
							if (key == key_esc) break;
							strcpy_s(cloned, MAX_MALOP, maLop.c_str());
							exist = CheckExistLop(cloned);
							if (!exist || maLop.empty()) {
								gotoXY(60, 10);
								SetColor(color_darkwhite | colorbk_red);
								cout << "Lop khong ton tai !";
							}
							else {
								if (key == key_Enter) {
									CommonShowSvList(context, context.ds_sv, menuCurrent->posStatus, cloned);
									maLop.clear();
								}
							}

						} while (key != key_esc || !exist);
						clrscr(40, 5, 90, 20, ' '); // bao gom form nhap ma lop 
					}
					break;
				}
				case 1: {
					SetColor(color_darkwhite);
					int keyRemove = -1;
					gotoXY(40, 3);
					cout << "F2: Xoa SV - F3: Sua SV - ESC: Thoat";
					do
					{
						keyRemove = CommonShowSvList(context, context.ds_sv, menuCurrent->posStatus, NULL);
					} while (keyRemove != key_esc);
					break;
				}
				case 2: { // Nhap ds sinh vien
					if (key == key_Enter) {
						SetColor(color_darkwhite);
						bool masv_null = false;
						string textFields[7] = { "" };
						int maxTexts[7] = { MAX_MALOP - 1, MAX_MASV - 1,
							MAX_HO - 1,MAX_TEN - 1, MAX_PHAI - 1,MAX_SDT - 1,4 };
						gotoXY(60, 3);
						cout << "Nhap MASV rong de ket thuc nhap!";
						do
						{
							int key = -1;
							SetColor(color_white | colorbk_green);
							rectagle(45, 7, 65, 25);
							SetColor(color_white);
							key = DrawFormInputSinhVien(70, 8, 30, textFields, maxTexts, 7, false);
							if (key == key_Enter) {
								if (textFields[0].empty()) {
									masv_null = true;
									break;
								}
								if (!CheckInputBoxIsNull(textFields, 7)) {
									// validate data
									NODE_SINH_VIEN* sv = new NODE_SINH_VIEN;
									strcpy_s(sv->data.MASV, MAX_MASV, textFields[0].c_str());
									if (CheckExistMSSV(context.ds_sv, sv->data.MASV)) {
										gotoXY(60, 31);
										SetColor(color_red);
										string a = "Ma sinh vien da ton tai. Kiem tra lai !";
										cout << a;
										SetColor(color_red | colorbk_green);
										ClearMessage(60, 31, a.length());
									}
									else if (textFields[4] != "NAM" && textFields[4] != "NU") {
										gotoXY(60, 31);
										SetColor(color_red);
										string a = "Gioi tinh phai la: \"Nam\" or \"Nu\"";
										cout << a;
										SetColor(color_red | colorbk_green);
										ClearMessage(60, 31, a.length());
										continue;
									}
									else if (atoi(textFields[6].c_str()) < 2000 && atoi(textFields[6].c_str()) <= 2050) {
										gotoXY(60, 31);
										SetColor(color_red | colorbk_black);
										string a = "Nam nhap hoc >= 2000 va <= 2050";
										cout << a;
										SetColor(color_red | colorbk_green);
										ClearMessage(60, 31, a.length());
									}
									else {
										strcpy_s(sv->data.MALOP, MAX_MALOP, textFields[1].c_str());
										strcpy_s(sv->data.HO, MAX_HO, textFields[2].c_str());
										strcpy_s(sv->data.TEN, MAX_TEN, textFields[3].c_str());
										strcpy_s(sv->data.PHAI, MAX_PHAI, textFields[4].c_str());
										strcpy_s(sv->data.SDT, MAX_SDT, textFields[5].c_str());
										sv->data.NAMNHAPHOC = atoi(textFields[6].c_str());
										sv->pNext = NULL;
										bool exist = CheckExistLop(sv->data.MALOP);
										if (!exist) {
											InsertLopIntoDSLop(sv->data.MALOP);
										}
										InsertAndSortSvIntoDS(context.ds_sv, sv);
										UpdateListStudentToFile(context.ds_sv);

										gotoXY(60, 31);
										SetColor(color_red);
										string a = "Ghi sinh vien thanh cong!";
										cout << a;
										ClearMessage(60, 31, a.length());
										for (int i = 0; i < 7; i++)
										{
											textFields[i].clear();
										}
									}
								}
								else {
									gotoXY(60, 31);
									SetColor(color_red);
									string a = "Du lieu nhap khong duoc de trong!";
									cout << a;
									SetColor(color_red | colorbk_green);
									ClearMessage(60, 31, a.length());
								}
							}
						} while (masv_null == false);
						clrscr(40, 3, 90, 35, ' ');
						break;
					}
				}
				default: {
					break;
				}
				}
			}
		}
		else if (menuCurrent == &MenuMonHoc) {
			if (key == key_esc) {
				menuCurrent = &MenuFeatures;
				clrscr(3, 18, 20, 3 * menuCurrent->n, ' ');
			}
			else {
				switch (menuCurrent->posStatus) {

				case 0: {
					if (key == key_Enter) {
						SetColor(color_darkwhite);
						SortMonHocByNameMH(context.ds_mh);
						InDanhSachMonHoc(context, context.ds_mh, 40, 10, menuCurrent->posStatus);
					}
					break;
				case 1: {
					if (key == key_Enter) {
						// TODO: implement remove/update feature of the subject
						int keyRemove = -1;
						SetColor(color_darkwhite);
						gotoXY(40, 3);
						cout << "F2: Xoa MH - F3: Sua MH - ESC: Thoat";
						do
						{
							SortMonHocByNameMH(context.ds_mh);
							keyRemove = InDanhSachMonHoc(context, context.ds_mh, 40, 10, menuCurrent->posStatus);
						} while (keyRemove != key_esc);
						break;
					}
				}
				case 2: {
					if (key == key_Enter) {
						SetColor(color_darkwhite);
						bool mamh_null = false;

						string textFields[4] = { "" };
						int maxTexts[4] = { MAX_MAMH - 1, MAX_TENMH - 1, 4, 4 };
						gotoXY(60, 3);
						cout << "Nhap Ma MH rong de ket thuc nhap!";
						do
						{
							int key = -1;
							SetColor(color_white | colorbk_green);
							rectagle(45, 5, 65, 15);
							SetColor(color_white);
							key = DrawFormInputMonHoc(70, 6, 30, textFields, maxTexts, 4, false);
							if (key == key_Enter) {
								if (textFields[0].empty()) {
									mamh_null = true;
									break;
								}
								if (!CheckInputBoxIsNull(textFields, 4)) {
									// validate data
									MON_HOC* mh = new MON_HOC;
									strcpy_s(mh->MAMH, MAX_MAMH, textFields[0].c_str());
									if (CheckExistMaMH(context.ds_mh, mh->MAMH)) {
										gotoXY(60, 19);
										SetColor(color_red);
										string a = "Ma mon hoc da ton tai. Kiem tra lai !";
										cout << a;
										Sleep(1500);
									}
									else {
										strcpy_s(mh->TENMH, MAX_TENMH, textFields[1].c_str());
										mh->STCLT = atoi(textFields[2].c_str());
										mh->STCTH = atoi(textFields[3].c_str());
										context.ds_mh.ds[context.ds_mh.n] = mh;
										context.ds_mh.n++;
										UpdateFileDSMonHoc(context.ds_mh);

										gotoXY(60, 19);
										SetColor(color_red);
										string a = "Ghi mon hoc thanh cong!";
										cout << a;
										Sleep(1500);
										for (int i = 0; i < 4; i++)
										{
											textFields[i].clear();
										}
									}
								}
								else {
									gotoXY(60, 19);
									SetColor(color_red);
									string a = "Du lieu nhap khong duoc de trong!";
									cout << a;
									Sleep(1500);
								}
							}
						} while (mamh_null == false);
						clrscr(40, 3, 90, 35, ' ');
						break;
					}
				}
				default:
					break;
				}
				}
			}
		}
	} while (true);
}
int ProcessControl_SV(AppContext& context) {

	MenuContent* menuCurrent = &MenuFeatureSv;

	do {
		int key = ControlMenu(menuCurrent, color_darkwhite, color_green);

		if (menuCurrent == &MenuFeatureSv) {
			if (key == key_Enter)
				switch (menuCurrent->posStatus)
				{
				case 0://menu lop  tin chi
				{
					key = ControlSinhVienDkyLTC(context, menuCurrent->posStatus);
					if (key == key_esc) {
						menuCurrent->posStatus;
						break;
					}
				}
				default:
					break;
				}
			else if (key == key_esc) {
				menuCurrent = &ActionConfirm;
				ConfirmDialog("Xac nhan dang xuat ?");
				key = ControlMenu(menuCurrent, 7, 12);
				if (key == key_Enter && menuCurrent->posStatus == 0) {
					return key;
				}
				else {
					menuCurrent = &MenuFeatureSv;
					clrscr(50, 5, 40, 14, ' ');
				}
			}
		}
	} while (true);
}
void DrawMainLayout(string currentUser, bool isStudent) {
	HideCursor(true); // hide cursor
	rectagle(1, 1, 25, 40);
	// where is place content when have a action
	rectagle(26, 1, 120, 40);
	if (!isStudent) {
		DrawListMenu(MenuFeatures, 4);
	}
	else {
		DrawListMenu(MenuFeatureSv, 1);
	}
	SetColor(color_darkwhite);
	ShowGuide();
	gotoXY(6, 2);
	SetColor(color_darkwhite | colorbk_darkred);
	cout << "CHUC NANG CHINH";

	// show current user
	gotoXY(115, 2);
	SetColor(color_darkwhite);
	cout << "Ma sv: " << currentUser;
}
#endif // !MENU_H
