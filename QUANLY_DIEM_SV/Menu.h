#pragma once
string mainActions[4] = { "CHUC NANG LOP TIN CHI", "CHUC NANG SINH VIEN", "CHUC NANG MON HOC", "CHUC NANG DIEM" };
string nameAction = "";
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


struct MenuItem {
	RECT rect;
	std::string name;
};
struct MenuContent {
	MenuItem* menus = NULL;
	int n = 0;
	int posStatus = 0;
};
MenuContent MenuFeatures = {
	new MenuItem[4] {
	{{3,3,20,2},"Lop Tin Chi"},
	{{3,6,20,2},"SinhVien"},
	{{3,9,20,2},"Mon Hoc"},
	{{3,12,20,2},"Diem"}
	},
	 4
};

MenuContent MenuMonHoc = {
	new MenuItem[3] {
		{{3,18,20,2},"Them MH"},
		{{3,21,20,2},"Xoa or Sua (MH)"},
		{{3,24,20,2},"In danh sach MH"}
	},
	 3
};

MenuContent MenuSinhVien = {
	new MenuItem[3] {
		{{3,18,20,2},"Nhap Sinh Vien"},
		{{3,21,20,2},"Xoa or Sua (SV)"},
		{{3,24,20,2},"In danh sach SV"},
	},
	 3
};

MenuContent MenuLopTinChi = {
	new MenuItem[3] {
	{{3,18,20,2},"Them Lop TC"},
	{{3,21,20,2},"Xoa or Sua (TC)"},
	{{3,24,20,2},"In danh sach TC"},
	},
	 3
};
MenuContent MenuDiem = {
	new MenuItem[2] {
	{{3,18,20,2},"Nhap diem"},
	{{3,21,20,2},"Xem diem"},
	},
	 2
};

MenuContent ActionQuit = {
	new MenuItem[2] {
		{{55, 12, 10, 2},"Ok"},
	{{68, 12, 10, 2},"Cancel"},
	},
	 2
};

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

void HideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
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

int ControlMenu(MenuContent* menucontent, int defaultColor = color_darkwhite, int activateColor = color_green) {
	int pos = menucontent->posStatus;
	int key = -1;
	DrawListMenu(*menucontent, defaultColor);
	DrawEachButtonOfAction(menucontent->menus[pos], activateColor);

	do
	{
		key = inputKey();
		switch (key)
		{
		case key_Up: {
			if (pos == 0) {
				pos = menucontent->n;
			}
			pos -= 1;
			goto paint;
		}
		case key_tab:
		case key_Down: {
			if (pos == menucontent->n - 1) {
				pos = -1;
			}
			pos += 1;
			goto paint;
		}
		case key_Enter: {
			if (pos == 0) {
				DrawListMenu(MenuMonHoc, 3);
				//DrawLo
			}
		}
		default:
			break;
		paint: {
			DrawEachButtonOfAction(menucontent->menus[menucontent->posStatus]);
			DrawEachButtonOfAction(menucontent->menus[pos], activateColor);
			menucontent->posStatus = pos;
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

void ProcessConrtol() {

	MenuContent* meunuCurrent = &MenuFeatures;

	do {
		int key = ControlMenu(meunuCurrent);

		if (meunuCurrent == &MenuFeatures) {
			if (key == key_Enter)
				switch (meunuCurrent->posStatus)
				{
				case 0://menu lop  tin chi
				{
					meunuCurrent = &MenuLopTinChi;
					break;
				}
				case 1: {
					meunuCurrent = &MenuSinhVien;
					break;
				}
				case 2: {
					meunuCurrent = &MenuMonHoc;
					break;
				}
				case 3: {
					meunuCurrent = &MenuDiem;
					break;
				}
				default:
					break;
				}
		}

		if (meunuCurrent == &MenuLopTinChi) {
			if (key == key_esc) {
				meunuCurrent = &MenuFeatures;
				clrscr(3, 18, 20, 3 * meunuCurrent->n, ' ');
			}
			else {
				switch (meunuCurrent->posStatus) {
				case 0: {
					DrawContentLopTC();
				}
				default:
					break;
				}
			}
		}
		else if (meunuCurrent == &MenuSinhVien) {
			if (key == key_esc) {
				meunuCurrent = &MenuFeatures;
				clrscr(3, 18, 20, 3 * meunuCurrent->n, ' ');
			}
			else switch (meunuCurrent->posStatus)
			{
			default:
				break;
			}
		}
		else if (meunuCurrent == &MenuMonHoc) {
			if (key == key_esc) {
				meunuCurrent = &MenuFeatures;
				clrscr(3, 18, 20, 3 * meunuCurrent->n, ' ');
			}
			else switch (meunuCurrent->posStatus)
			{
			default:
				break;
			}
		}
		else if (meunuCurrent == &MenuDiem) {
			if (key == key_esc) {
				meunuCurrent = &MenuFeatures;
				clrscr(3, 18, 20, 3 * meunuCurrent->n, ' ');
			}
			else switch (meunuCurrent->posStatus)
			{
			default:
				break;
			}
		}
		else {
			meunuCurrent = &ActionQuit;
			ConfirmQuit();
			key = ControlMenu(meunuCurrent);
			if (key == key_Enter && meunuCurrent->posStatus == 0) {
				return;
			}
			else {
				meunuCurrent = &MenuFeatures;
				clrscr(50, 5, 40, 14, ' ');
			}
		}


		/*	if (key == key_esc && posMenu == 0) {
				SetColor(color_darkgreen);
				CHAR_INFO* ch = NULL;
				ReadBlockChar(ch, 13, 41, 50, 5);
				ConfirmQuit();
				key = ControlMenu(menus[2], statusPos[2], indexLast[2]);
				if (key == key_Enter && statusPos[2] == 0) {
					return;
				}
				WriteBlockChar(ch, 13, 41, 50, 5);
			}
			else if (key == key_Enter && posMenu == 0) {
				if (statusPos[posMenu] == 0) {
					posMenu = 1;

				}
				DrawListMenu(menus[posMenu], indexLast[posMenu] + 1);
			}
			else if (key == key_esc && posMenu == 1)
			{
				posMenu = 0;
				clrscr(3, 18, 20, 3 * 3, ' ');
			}*/
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
	ShowGuide();
	gotoXY(4, 2);
	cout << "CHUC NANG CHINH";
}
