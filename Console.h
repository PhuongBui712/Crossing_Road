extern bool THEME, SOUND;
#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <windows.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <thread>
#include <vector>
using namespace std;

#pragma execution_character_set("UTF-8")
#pragma comment (lib, "winmm.lib") 

#define WIDTH_CONSOLE  1300
#define HEIGHT_CONSOLE 725
#define HELP_GET_SIZE 100

// Mỗi ô người di chuyển ngang 5 cao 5 (riêng xe ngang 21)
#define TILE_X 5
#define TILE_Y 5
#define TILE_X_CAR 15

// Số lượng ô trong khung game
#define MAX_MASK_X 24
#define MAX_MASK_Y 6

#define COLUMS Console::getSize() / HELP_GET_SIZE
#define ROWS Console::getSize() % HELP_GET_SIZE

// Tọa độ viền của khung game
enum class Border {
	LEFT = 10,
	RIGHT = TILE_X * MAX_MASK_X + LEFT,
	TOP = 4,
	BOTTOM = TILE_Y * MAX_MASK_Y + TOP
};

enum class Color {
	BLACK, 
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	LIGHT_GRAY,									
	GRAY,										
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	LIGHT_YELLOW,								
	WHITE										
};


class Console {
public:
	// Thay đổi màn hình console (thay đổi và cố định kích thước)
	static void resizeConsole(int width, int height);
	static void fixConsoleWindow();

	// Thao tác con trỏ 
	static void gotoXY(int x, int y);
	static void showCursor(bool CursorVisibility);

	// Thay đổi màu
	static void setColor(int x);

	// Xóa màn hình console
	static void clearScreen();

	// Vẽ
	static void drawFromFile(const string, COORD, int);
	static void removeSpace(short, short, bool isCar = 0);
	static void removeSpace(short, short, short, short);


	// Lấy kích thước của console
	static int getSize();
	static int getMidVertical();
	static int getMidHorizontal();

	// Khác
	static void setConsole();
};
#endif