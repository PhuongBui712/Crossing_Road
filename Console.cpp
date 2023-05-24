#include "Console.h"

/// 
/// - - - - - - - - - - - - CONSOLE - - - - - - - - - - - - 
/// 

// Vô hiệu hoá nút phóng to màn hình
void Console::fixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

// Thay đổi kích thước màn hình
void Console::resizeConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

/// 
/// - - - - - - - - - - - - CON TRỎ - - - - - - - - - - - - 
/// 

// Di chuyển con trỏ đến một vị trí
void Console::gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Đổi màu
void Console::setColor(int x) {
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!THEME) {
		if (x < 15) {
			SetConsoleTextAttribute(mau, x + 240);
		}
		else if (x == 15) {
			SetConsoleTextAttribute(mau, 240);
		}
		else if (x > 15 && x < 240) {
			SetConsoleTextAttribute(mau, x);
		}
		else if (x == 240)
			SetConsoleTextAttribute(mau, 15);
		else
			SetConsoleTextAttribute(mau, x % 15);
	}
	else
		SetConsoleTextAttribute(mau, x);
}

// Ẩn/ Hiện con trỏ
void Console::showCursor(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

// Xoá toàn bộ console
void Console::clearScreen() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

// Vẽ từ file
void Console::drawFromFile(string filename, COORD pos, int color) {
	string str;
	ifstream f(filename);
	setColor(color);

	if (f.is_open()) {
		while (not f.eof()) {
			getline(f, str);
			gotoXY(pos.X, pos.Y);
			cout << str;
			pos.Y++;
		}
	}
	else {
		cerr << "Cannot find the " << filename << "\n";
	}
	f.close();

	setColor((int)Color::WHITE);
}

// Xóa người hoặc động vật hoặc xe (Hàm này cần xem lại tất cả hình vẽ rồi chỉnh lại cho đồng nhất)
void Console::removeSpace(short x, short y, bool isCar) {
	if (!isCar) {
		for (int i = y; i < y + 3; i++) {
			Console::gotoXY(x, i);
			cout << string(TILE_X, ' ');
		}
	}
	else {
		for (int i = y; i < y + 4; i++) {
			Console::gotoXY(x, i);
			cout << string(TILE_X_CAR, ' ');
		}
	}
}

void Console::removeSpace(short x, short y, short _x, short _y) {
	setColor((int)Color::WHITE);
	for (int i = y; i <= _y; i++) {
		gotoXY(x, i);
		cout << string(static_cast<long>(_x) - static_cast<long>(x) + 1, ' ');
	}
}

// Hỗ trợ lấy vị trí chính giữa của console
int Console::getSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return columns * HELP_GET_SIZE + rows;
}

// Lấy vị trí chính giữa của chiều cao
int Console::getMidVertical() {
	int size = getSize();
	return (size % HELP_GET_SIZE) / 2;
}

// Lấy vị trí chính giữa của chiều ngang
int Console::getMidHorizontal() {
	int size = getSize();
	return (size / HELP_GET_SIZE) / 2;
}

// Thiết lập console mặc định
void Console::setConsole() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	fixConsoleWindow();
	resizeConsole(WIDTH_CONSOLE, HEIGHT_CONSOLE);
	SetConsoleTitle(L"ROADCROSSING TEAM 9");
	showCursor(false);
}