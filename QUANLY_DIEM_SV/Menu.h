#ifndef MENU_H
#define MENU_H

#include "Structure.h"


string openLogin() {
	rectagle(40, 10, 50, 15);
	gotoXY(45, 13);
	cout << "Username";
	rectagle(45, 14, 25, 2); // width of input

	gotoXY(45, 18);
	cout << "Password";
	rectagle(45, 19, 25, 2);
	gotoXY(47, 15);

	string auth[2];
	int pos = 0;
	int key = -1;
	string masv = "";
	do {
		key = inputKey();
		switch (key)
		{
		case key_Up: {
			pos = 0;
			gotoXY(47 + auth[pos].length(), 15);
			break;
		}
		case key_Down: {
			pos = 1;
			gotoXY(47 + auth[pos].length(), 20);
			break;
		};
		case key_tab: {
			pos = (pos + 1) % 2;
			if (pos == 0) {
				gotoXY(47 + auth[pos].length(), 15);
			}
			else {
				gotoXY(47 + auth[pos].length(), 20);
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
			if (auth[0] == "sv" && auth[1] == "sv") {
				masv = auth[0];
				return masv;
			}
			else {
				gotoXY(47, 24);
				cout << "Thong tin dang nhap khong dung!";
				gotoXY(47 + auth[pos].length(), pos == 0 ? 15 : 20);
				break;
			}
		}
		default:
			if (key > 31 && key < 127) {
				if (pos == 0) {
					gotoXY(47 + auth[pos].length(), 15);
				}
				else {
					gotoXY(47 + auth[pos].length(), 20);
				}
				if (auth[pos].length() < 20) {
					auth[pos] += key;
					if (pos == 0) {
						cout << char(key);
					}
					else {
						cout << "*";
					}
				}
			}
			break;
		}
	} while (key != key_esc || masv.length() > 0);
	cout << "Thoat";
	return masv;
}

void SetCurrentAction(int actionIndex) {
	int location = 80;
	for (int i = mainActions[actionIndex].length() - 1; mainActions[actionIndex].length() < 0; i--)
	{
		cout << 1;
		gotoXY(location + mainActions[actionIndex].length(), 2);
		cout << "\b \b";
		mainActions->erase(mainActions[actionIndex].length() - 1, 1);
	}
	nameAction = "";
	nameAction = mainActions[actionIndex];
	gotoXY(80, 2);
	cout << nameAction;
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

void ProcessConrtol(AppContext& context) {

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
					menuCurrent = &MenuDiem;
					break;
				}
				case 4: {
					// TODO: Sinh Vien Dang Ky Lop Tin Chi
					key = ControlSinhVienDkyLTC(context, menuCurrent->posStatus, color_darkwhite, color_green);
					if (key == key_esc) {
						menuCurrent->posStatus;
						break;
					}
				}
				default:
					break;
				}
			else if (key == key_esc) {
				menuCurrent = &ActionQuit;
				ConfirmQuit();
				key = ControlMenu(menuCurrent, color_darkwhite, color_green);
				if (key == key_Enter && menuCurrent->posStatus == 0) {
					return;
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
						InDanhSachLopTinChi(context.ds_mh, context.tree, context.ds, context.nLTC, 40, 10, menuCurrent->posStatus);
					}
					break;
				}
				case 1: {
					SetColor(color_darkwhite);
					int keyRemove = -1;
					do
					{
						context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
						context.nLTC = 0;
						ConvertTreeToArray(context.tree, context.ds, context.nLTC);
						keyRemove = InDanhSachLopTinChi(context.ds_mh, context.tree, context.ds, context.nLTC, 40, 10, menuCurrent->posStatus);
					} while (keyRemove != key_esc);
					break;
				}
				case 2: {
					string Texts[6] = { "" };
					int maxTexts[6] = { MAX_MAMH - 1, MAX_NIENKHOA - 1,3,3,3,3 };
					int key = -1;
					SetColor(color_darkwhite);
					while (key != key_esc)
					{
						key = DrawFormInputLTC(70, 5, 30, Texts, maxTexts, 6, false);
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
								p->MALOPTC = RandomIDLTC(context.tree);
								p->ds_sv_dky = NULL;
								if (CheckExistMaMH(context.ds_mh, p->MAMH)) {
									context.ds = CreateArrayLopTinChi(context.nLTC, sizeof(Lop_Tin_Chi));
									ConvertTreeToArray(context.tree, context.ds, context.nLTC);
									bool exist = CheckLopTinChiToInsert(context.ds, context.nLTC, p);
									if (!exist) {
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
										gotoXY(60, 36);
										cout << "Them lop tin chi thanh cong !";
									}
									else {
										gotoXY(60, 36);
										cout << "Thong tin lop tin chi da ton tai. Kiem tra lai !";
									}
								}
								else {
									gotoXY(60, 36);
									cout << "Ma mon hoc khong ton tai. Kiem tra lai !";
								}
							}
							else {
								gotoXY(60, 36);
								cout << "Du lieu nhap khong duoc de trong!";
							}
						}
					}
					clrscr(50, 5, 90, 35, ' ');
					break;
				}
				case 3: {
					// Show list sv by conditions
					Search_GV_LTCByConditions(context, menuCurrent->posStatus);
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
						string maLop[1] = { "" };
						int maxTexts[1] = { MAX_MALOP - 1 };
						int key = -1;
						char cloned[MAX_MALOP];
						bool exist = false;
						do
						{
							SetColor(color_darkwhite);
							key = DrawFormInputSinhVien(60, 5, 30, maLop, maxTexts, 1, false);
							if (key == key_esc) break;
							strcpy_s(cloned, MAX_MALOP, maLop[0].c_str());
							exist = CheckExistLop(cloned);
							if (!exist || maLop[0].empty()) {
								gotoXY(60, 10);
								SetColor(color_darkwhite | colorbk_red);
								cout << "Lop khong ton tai !";
							}
							else {
								if (key == key_Enter) {
									CommonShowSvList(context.ds_sv, menuCurrent->posStatus, cloned);
									maLop[0].clear();
								}
							}

						} while (key != key_esc || !exist);
						clrscr(40, 5, 90, 20, ' '); // bao gom form nhap ma lop 
					}
					break;
				}
				case 1: {
					SetColor(color_darkwhite);
					/*string maLop[1] = { "" };
					int maxTexts[1] = { MAX_MALOP - 1 };
					char cloned[MAX_MALOP];
					bool exist = false;*/
					int keyRemove = -1;
					do
					{
						keyRemove = CommonShowSvList(context.ds_sv, menuCurrent->posStatus, NULL);
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
						do
						{
							int key = -1;
							key = DrawFormInputSinhVien(70, 5, 30, textFields, maxTexts, 7, false);
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
										gotoXY(60, 36);
										cout << "Ma sinh vien da ton tai. Kiem tra lai !";
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

										gotoXY(60, 36);
										cout << "Ghi sinh vien thanh cong!";
										for (int i = 0; i < 7; i++)
										{
											textFields[i].clear();
										}
									}
								}
								else {
									gotoXY(60, 36);
									cout << "Du lieu nhap khong duoc de trong!";
									/*Sleep(3000);
									clrscr(60, 36, 40, 3, ' ');*/
								}
							}
						} while (masv_null == false);
						clrscr(50, 5, 90, 35, ' ');
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
						SortMonHocMyNameMH(context.ds_mh);
						InDanhSachMonHoc(context.ds_mh, 40, 10, menuCurrent->posStatus);
					}
					break;
				case 1: {
					if (key == key_Enter) {
						// TODO: implement remove/update feature of the subject
						int keyRemove = -1;
						SetColor(color_darkwhite);
						do
						{
							SortMonHocMyNameMH(context.ds_mh);
							keyRemove = InDanhSachMonHoc(context.ds_mh, 40, 10, menuCurrent->posStatus);
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
						do
						{
							int key = -1;
							key = DrawFormInputMonHoc(70, 5, 30, textFields, maxTexts, 4, false);
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
										gotoXY(60, 25);
										cout << "Ma mon hoc da ton tai. Kiem tra lai !";
									}
									else {
										strcpy_s(mh->TENMH, MAX_TENMH, textFields[1].c_str());
										mh->STCLT = atoi(textFields[2].c_str());
										mh->STCTH = atoi(textFields[3].c_str());
										context.ds_mh.ds[context.ds_mh.n] = mh;
										context.ds_mh.n++;
										UpdateFileDSMonHoc(context.ds_mh);

										gotoXY(60, 25);
										cout << "Ghi mon hoc thanh cong!";
										for (int i = 0; i < 4; i++)
										{
											textFields[i].clear();
										}
									}
								}
								else {
									gotoXY(60, 25);
									cout << "Du lieu nhap khong duoc de trong!";
									/*Sleep(3000);
									clrscr(60, 36, 40, 3, ' ');*/
								}
							}
						} while (mamh_null == false);
						clrscr(50, 5, 90, 35, ' ');
						break;
					}
				}
				default:
					break;
				}
				}
			}
		}
		else if (menuCurrent == &MenuDiem) {
			if (key == key_esc) {
				menuCurrent = &MenuFeatures;
				clrscr(3, 18, 20, 3 * menuCurrent->n, ' ');
			}
			else switch (menuCurrent->posStatus)
			{
			default:
				break;
			}
		}
	} while (true);
}
void DrawMainLayout(string currentUser) {
	HideCursor(true); // hide cursor
	// main actions
	rectagle(1, 1, 25, 40);
	// where is place content when have a action
	rectagle(26, 1, 120, 40);
	DrawListMenu(MenuFeatures, 4);

	//DrawContentLopTC();

	//DrawContentMonHoc();
	SetColor(color_darkwhite);
	ShowGuide();
	gotoXY(6, 2);
	SetColor(color_darkwhite | colorbk_darkred);
	cout << "CHUC NANG CHINH";
}



#endif // !MENU_H
