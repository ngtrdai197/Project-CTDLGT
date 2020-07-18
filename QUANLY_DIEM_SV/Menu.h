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
	} while (key != 27 || masv.length() > 0);
	cout << "Thoat";
	return masv;
}


struct MenuItem {
	RECT rect;
	std::string name;
};

MenuItem MenuFeatures[] = {
	{{3,3,20,2},"Lop Tin Chi"},
	{{3,6,20,2},"SinhVien"},
	{{3,9,20,2},"Mon Hoc"},
	{{3,12,20,2},"Diem"},
};

MenuItem MenuCRUD[] = {
	{{3,18,20,2},"Them"},
	{{3,21,20,2},"Xoa"},
	{{3,24,20,2},"Sua"},
};

void DrawEachButtonOfAction(MenuItem& item) {
	rectagle(item.rect.left, item.rect.top, item.rect.right, item.rect.bottom);
	gotoXY((item.rect.right / 2) - 1, item.rect.top + 1);
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



void DrawListMenu(MenuItem menus[], int size) {
	for (int i = 0; i < size; i++)
	{
		DrawEachButtonOfAction(menus[i]); // +3
	}
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

int ControlMenu(MenuItem menuitems[], int& posStatus,int indexlast) {
	int pos = posStatus;
	int key = -1;
	SetColor(FOREGROUND_RED);
	DrawEachButtonOfAction(menuitems[posStatus]);

	do
	{
		key = inputKey();
		switch (key)
		{
		case key_Up: {
			if (pos == 0) {
				pos = indexlast+1;
			}
			pos -= 1;
			goto paint;
		}
		case key_Down: {
			if (pos == indexlast) {
				pos = -1;
			}
			pos += 1;
			goto paint;
		}

		default:
			//SetColor(0x0030 | 0x0004);
			break;
		paint: {
			SetColor(7);
			DrawEachButtonOfAction(menuitems[posStatus]);
			SetColor(FOREGROUND_RED);
			DrawEachButtonOfAction(menuitems[pos]);
			posStatus = pos;
			}
		}

	} while (key != 27 && key != key_Enter && key != key_tab);
	return key;
}

void DrawContentRight() {
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
void ProcessConrtol() {
	MenuItem* menus[] = {
		MenuFeatures,
		MenuCRUD
	};

	int StatusPos[] = { 0,0 };
	int indexlast[] = { 3,2 };

	int posMenu = 0;



	do {
		int key = ControlMenu(menus[posMenu], StatusPos[posMenu],indexlast[posMenu]);
		if (key == key_Enter && posMenu == 0) {
			posMenu = 1;
		}
		else
		{
			posMenu = (posMenu + 1) % 2;
		}
	} while (true);
}
void DrawMainLayout(string currentUser) {
	HideCursor(); // hide cursor
	// main actions
	rectagle(1, 1, 25, 40);
	// where is place content when have a action
	rectagle(26, 1, 120, 40);
	DrawListMenu(MenuFeatures,4);
	DrawListMenu(MenuCRUD,3);
	DrawContentRight();

	ShowGuide();


	gotoXY(4, 2);
	cout << "CHUC NANG CHINH";


}
