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

void DrawEachButtonOfAction(MenuItem& item, int color = color_darkwhite) {
	SetColor(color);
	rectagle(item.rect.left, item.rect.top, item.rect.right, item.rect.bottom);
	gotoXY(item.rect.left + (item.rect.right - item.name.length()) / 2, item.rect.top + 1);
	cout << item.name;
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

void DrawListMenu(MenuContent& menucontent, int color = color_darkwhite) {
	for (int i = 0; i < menucontent.n; i++)
	{
		DrawEachButtonOfAction(menucontent.menus[i], color); // +3
	}
}

void ConfirmQuit() {
	rectagle(50, 5, 40, 13);
	gotoXY(55, 8);
	cout << "Ban co muon thoat chuong trinh";
	DrawListMenu(ActionQuit);

}

void HideCursor(bool ishide = true)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = !ishide;
	SetConsoleCursorInfo(consoleHandle, &info);
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
					 //case key_Enter: {
					 //	if (pos == 0) {
					 //		DrawListMenu(MenuMonHoc, 3);
					 //		//DrawLo
					 //	}
					 //}
		default:
			break;
		paint: {
			DrawEachButtonOfAction(menuContent->menus[menuContent->posStatus]);
			DrawEachButtonOfAction(menuContent->menus[pos], activateColor);
			menuContent->posStatus = pos;
			}
		}

	} while (key != key_esc && key != key_Enter);
	return key;
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
char InputBox(string& str, int x, int y, int width, int maxText, bool isDraw = false, bool isText = true) {
	string text = str;
	SetColor(color_darkwhite);
	rectagle(x, y, width, 2);

	if (isDraw) return -1;

	char key = -1;
	gotoXY(x + 1, y + 1);
	cout << text;
	HideCursor(false);

	do {
		key = inputKey();

		if (isText ?
			(((
				(key > 47 && key < 58) || (key > 64 && key < 91) || (key > 96 && key < 123)) || key == 45) && text.length() < maxText)
			: ((key > 47 && key < 58) && text.length() < maxText)) {
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

	HideCursor();
	str = text;
	return key;
}

char DrawFormInput(int x, int y, int width, string Texts[], int maxText[], int n) {

	int offset = 3;

	for (int i = 0; i < n; i++)
	{
		// index > 2 enter number else enter string
		InputBox(Texts[i], x, y + (i * offset), width, maxText[i], true, i < 2 ? true : false);
	}

	int indexCurrent = 0;
	int key = -1;

	do
	{
		key = InputBox(Texts[indexCurrent], x, y + (indexCurrent * offset),
			width, maxText[indexCurrent], false, indexCurrent < 2 ? true : false);
		if (key == key_tab) {
			indexCurrent = (indexCurrent + 1) % n;
		}

	} while (key != key_esc && key != key_Enter);
	return key;
}

void ProcessConrtol(AppContext& context) {

	MenuContent* menuCurrent = &MenuFeatures;

	do {
		int key = ControlMenu(menuCurrent);

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
				default:
					break;
				}
			else if (key == key_esc) {
				menuCurrent = &ActionQuit;
				ConfirmQuit();
				key = ControlMenu(menuCurrent);
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
						ConvertTreeToArray(context.tree, context.ds, context.nLTC);
						InDanhSachLopTinChi(context.ds, context.nLTC, 30, 10);
						//delete[] context.ds;
						context.nLTC = 0;
					}
					break;
				}
				case 2: {
					string Texts[6] = { "" };
					int maxTexts[6] = { MAX_MAMH - 1, MAX_NIENKHOA - 1,3,3,3,3 };
					int key = -1;
					while (key != key_esc)
					{
						key = DrawFormInput(115, 10, 30, Texts, maxTexts, 6);
						if (key == key_Enter) {
							if (!CheckInputBoxNull(Texts, 6)) {
								// validate data
								Lop_Tin_Chi* p = new Lop_Tin_Chi;
								strcpy_s(p->MAMH, MAX_MAMH, Texts[0].c_str());
								strcpy_s(p->NIEN_KHOA, MAX_NIENKHOA, Texts[1].c_str());
								p->HOC_KY = stoi(Texts[2]);
								p->NHOM = stoi(Texts[3]);
								p->sv_max = stoi(Texts[4]);
								p->sv_min = stoi(Texts[5]);
								p->MALOPTC = RandomIDLTC(context.tree);
								p->ds_sv = NULL;
								if (CheckExistMaMH(context.ds_mh, p->MAMH)) {
									ConvertTreeToArray(context.tree, context.ds, context.nLTC);
									bool exist = CheckLopTinChiToInsert(context.ds, context.nLTC, p);
									if (!exist) {
										InsertNodeIntoTree(context.tree, p);
										context.nLTC = 0;
										ConvertTreeToArray(context.tree, context.ds, context.nLTC);
										UpdateListLopTinChiToFile(context.ds, context.nLTC);
										menuCurrent->posStatus = 0;
									}
								}
								delete p;
							}
							else {
								gotoXY(99, 11);
								cout << "Du lieu nhap khong duoc de trong!";
							}
							break;
						}
					}

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
						int total = context.ds_sv_original.totalSv;
						SINH_VIEN** ds_sv = CreateArraySV(total, sizeof(SINH_VIEN));
						ConvertLinkedListSV(context.ds_sv_original, ds_sv);
						InDanhSachSinhVien(ds_sv, total, 30, 10);
					}
					break;
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
						InDanhSachMonHoc(context.ds_mh, context.ds_mh.n, 30, 10);
					}
					break;
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
	HideCursor(); // hide cursor
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
