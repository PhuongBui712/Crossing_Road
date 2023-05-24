#ifndef _CGAME_H
#define _CGAME_H

#include "CPeople.h"
#include "CBird.h"
#include "CMonkey.h"
#include "CCar.h"
#include "CTruck.h"
#include "CHelicopter.h"
#include "CTraffic.h"

enum class Key {
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13
};

void SubThread();
void SoundThread();
void SoundMoveThread();
void SoundGameOverThread();
void SoundUpLevelThread();
void SoundWinThread();

class CGAME {
private:
	const string MAIN_MENU[4] = { "START GAME", "LOAD GAME ", "SETTINGS  ", "EXIT      " };
	const string SETTING_MENU[4] = { "THEME", "SOUND", "HEART", "   BACK    " };
	const string PAUSE_MENU[3] = { "CONTINUE ", "SAVE GAME", "MAIN MENU" };

	CBIRD* ac;			int ac_size;
	CMONKEY* ak;        int ak_size;
	CTRUCK* axt;		int axt_size;
	CCAR* axh;		    int axh_size;
	CHELICOPTER* att;   int att_size;
	CTRAFFIC* light;	int light_size = 3; //( 0: att, 1: axt, 2: axh)
	CPEOPLE* cn;
	
	short HEART;			// Mạng sống do người dùng chọn trong phần setting
	short DELAY;			// Hỗ trợ cho phần điều chỉnh tốc độ của level
	int LEVEL = 1;
	const int MAX_LEVEL = 13;
public:
	bool checkImpact = 0;
	bool IS_RUNNING;
	bool pressable = true;
	
	CGAME();
	~CGAME();

	// Vẽ
	void drawTitle();					// Title game
	void drawMainMenu(short choice);	// Menu chính
	void drawPauseMenu(short choice);	// Menu dừng game
	void clearPauseMenu();				// Xóa menu dừng game
	void drawSaveMenu();				// Menu save
	void drawLoadMenu();				// Menu load
	void clearSaveLoadMenu();			// Xóa menu save load
	void drawSettingMenu(short choice); // Setting menu
	
	void drawLevel();					// Vẽ level hiện tại
	void clearLevel();					// Xóa level
	void drawTime();					// Vẽ hiệu ứng lúc chuyển level
	void drawGame();					// Vẽ khung game
	void gameOver();					// Vẽ GameOver khi thua cuộc

	// Chạy menu
	short runMainMenu(thread*);
	short runPauseMenu();
	void runSettingMenu();

	// Getter
	CPEOPLE* getPeople() { return cn; };
	CANIMAL* getBird() { return ac; };
	CANIMAL* getMonkey() { return ak; };
	CVEHICLE* getTruck() { return axt; };
	CVEHICLE* getCar() { return axh; };
	CVEHICLE* getHelicopter() { return att; };
	int getBirdSize() { return ac_size; };
	int getMonkeySize() { return ak_size; };
	int getCarSize() { return axh_size; };
	int getTruckSize() { return axt_size; };
	int getHelicopterSize() { return att_size; };

	int getLevel() { return LEVEL; };
	int getMaxLevel() { return MAX_LEVEL; };
	short getDelay() { return DELAY; };
	int getHearts() { return cn->getHearts(); }

	// Thao tác game
	void resetGame();				// Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void startGame();					// Thực hiện bắt đầu vào trò chơi
	void exitGame(thread*);				// Thực hiện thoát Thread 
	bool pauseGame(thread*);			// Tạm dừng Thread (return 1 là tiếp tục game, return 0 là trở về main menu)
	void resumeGame(thread*);			// Quay lai Thread
	void setting();
	bool loadGame();
	void loadGame(thread* t);
	void saveGame(thread* t);			// Thực hiện lưu lại dữ liệu trò chơi
	void gameWinner();

	void createMobs(short tt_size, short c_size, short xt_size, short k_size, short xh_size);
	void updateLevel();								// Chỉnh độ khó theo level

	void upLevel();
	void updatePosPeople(char, thread*);			// Thực hiện điều khiển di chuyển của CPEOPLE
	void updatePosAnimal();							// Thực hiện cho CTRUCK & CCAR & CHELICOPTER di chuyển
	void updatePosVehical();						// Thực hiện cho CMONKEY & CBIRD di chuyển
	void runTraffic();								// Chạy thời gian đèn giao thông

	bool isWin();
	// Âm thanh khi xảy ra va chạm
	void soundImpact();
};
#endif

