#include "CGame.h"

// Tạo đối tượng mobs
template<class T>
void createObj(T*& obj, int size, short row, bool direction) {
	int column = (short)Border::LEFT;
	int distance = ((short)Border::RIGHT - (short)Border::LEFT) / size;

	if (obj != NULL)
		delete[] obj;

	obj = new T[size];
	for (int i = 0; i < size; i++) {
		obj[i].setX(column);
		obj[i].setDirection(direction);
		obj[i].setmY(row);
		column += distance;
	}
}

CGAME::CGAME() {
	Console::setConsole();
	IS_RUNNING = false;
	cn = new CPEOPLE;
	light = new CTRAFFIC[light_size];
	HEART = cn->MAX_HEARTS;
	LEVEL = 1;

	// Cài đặt đèn
	light[0].setmY(1);
	light[0].setStatus(TrafficLight::GREEN);
	light[0].setTimeGreen(10);
	// Xe tải
	light[1].setmY(3);
	light[1].setStatus(TrafficLight::GREEN);
	light[1].setTimeGreen(30);
	// Xe hơi
	light[2].setmY(5);
}

CGAME::~CGAME() {
	delete[] ac;
	delete[] ak;
	delete[] axh;
	delete[] axt;
	delete[] att;
	delete[] light;
	delete cn;
}

// Car ở menu chính
bool carRunning = 1;
void drawMenuCar() {
	static bool flag = 0;
	static COORD posCar = { 0,26 };
	while (carRunning) {
		Console::drawFromFile("Menu/Car.txt", posCar, (int)Color::GREEN);
		if (flag == 0)
			posCar.X++;
		else
			posCar.X--;
		if (posCar.X == COLUMS - 55)
			flag = 1;
		else if (posCar.X == 0)
			flag = 0;
		Sleep(50);
	}
}

// Tiêu đề game
void CGAME::drawTitle() {
	COORD pos = { 0,0 };
	Console::drawFromFile("Menu/Title.txt", pos, (int)Color::GRAY);
	Sleep(200);
	Console::drawFromFile("Menu/Title.txt", pos, (int)Color::LIGHT_RED);
	Sleep(200);
	Console::drawFromFile("Menu/Title.txt", pos, (int)Color::RED);
}

// Vẽ level hiện tại
void CGAME::drawLevel() {
	clearLevel();
	string level_file = "Level/Level title.txt";
	Console::drawFromFile(
		level_file,
		COORD{ (short)Border::LEFT + 98, 5 },
		(int)Color::RED
	);
	string level_number = to_string(LEVEL);
	for (short i = 0; i < level_number.size(); i++) {
		level_file = "Level/Number" + string(1, level_number[i]) + ".txt";
		Console::drawFromFile(level_file, COORD{ (short)((int)(Border::LEFT)+118 + i * 4), 5 }, (int)Color::RED);
	}
}

// Xóa level
void CGAME::clearLevel() {
	Console::removeSpace((int)Border::LEFT + 120, 5);
}

// Hiệu ứng chuyển level
void CGAME::drawTime() {
	Console::drawFromFile(
		"Map/EmptyFrame.txt",
		COORD{ (short)Border::LEFT - 2, (short)Border::TOP + 5 },
		(int)Color::LIGHT_GRAY
	);
	// Vẽ dòng Level <lv> ở chính giữa
	string level_file = "Level/Level title.txt";
	Console::drawFromFile(
		level_file,
		COORD{ (int)Border::LEFT + 51, (int)Border::TOP + 11 },
		(int)Color::YELLOW
	);
	string level_number = to_string(LEVEL);
	for (short i = 0; i < level_number.size(); i++) {
		level_file = "Level/Number" + string(1, level_number[i]) + ".txt";
		Console::drawFromFile(level_file, COORD{ (short)((int)Border::LEFT + 71 + i * 4), (short)((int)Border::TOP + 11) }, (int)Color::YELLOW);
	}
	// Vẽ thời gian
	string countdown_file;
	for (int time_coundown = 3; time_coundown != 0; time_coundown--) {
		countdown_file = "3s2s1s/" + to_string(time_coundown) + "s.txt";

		Console::drawFromFile(
			countdown_file,
			COORD{ (short)Border::LEFT + 58, (short)Border::TOP + 14 },
			(int)Color::YELLOW
		);
		Sleep(800);
		Console::removeSpace(
			(int)Border::LEFT + 58,
			(int)Border::TOP + 14,
			(int)Border::LEFT + 67,
			(int)Border::TOP + 22
		);
	}

	// Vẽ lại khung (nếu bị đè)
	Console::drawFromFile(
		"Map/EmptyFrame.txt",
		COORD{ (short)Border::LEFT - 2, (short)Border::TOP + 5 },
		(int)Color::WHITE
	);
}

// Vẽ màn hình chơi game
void CGAME::drawGame() {
	system("cls");
	Console::drawFromFile("Map/Frame.txt", COORD{ (short)Border::LEFT - 2, (short)Border::TOP - 1 }, (int)Color::WHITE);
	Console::drawFromFile("Map/ScoreBoard.txt", COORD{ (short)Border::RIGHT + 10, (short)Border::TOP - 1 }, (int)Color::WHITE);
	for (int i = 0; i < light_size; i++) {
		light[i].drawBody();
	}
	cn->drawHealthBar();
	cn->drawBody();
	drawLevel();
}

// Vẽ Menu chính 
void CGAME::drawMainMenu(short choice) {
	short count = 0;
	short midHoritonal = Console::getMidHorizontal(),
		midVertical = Console::getMidVertical();
	COORD pos = { midHoritonal - 5, midVertical - 2 };
	Console::drawFromFile("Menu/MainMenuFrame.txt", pos, (int)Color::YELLOW);

	for (auto& i : MAIN_MENU) {
		if (count == choice) {
			Console::setColor(16 * (int)Color::YELLOW);
			Console::gotoXY(pos.X + 2, pos.Y + count + 1);
			cout << i;
		}
		else {
			Console::setColor((int)Color::YELLOW);
			Console::gotoXY(pos.X + 2, pos.Y + count + 1);
			cout << i;
		}
		count++;
	}
}

// Vẽ Setting Menu
void CGAME::drawSettingMenu(short choice) {
	short count = 0;
	short midHoritonal = Console::getMidHorizontal(),
		midVertical = Console::getMidVertical();

	COORD pos = { midHoritonal - 5, midVertical - 2 };
	Console::drawFromFile("Menu/SettingMenuFrame.txt", pos, (int)Color::YELLOW);

	for (auto& i : SETTING_MENU) {
		if (count == choice) {
			Console::setColor(16 * (int)Color::YELLOW);
			Console::gotoXY(pos.X + 2, pos.Y + count + 1);
			if (count == 0) cout << i << ": " << (THEME ? "DARK " : "LIGHT");
			if (count == 1) cout << i << ": " << (SOUND ? "ON   " : "OFF  ");
			if (count == 2) cout << i << ": " << HEART << "    ";
			if (count == 3) cout << i;
		}
		else {
			Console::setColor((int)Color::YELLOW);
			Console::gotoXY(pos.X + 2, pos.Y + count + 1);
			if (count == 0) cout << i << ": " << (THEME ? "DARK " : "LIGHT");
			if (count == 1) cout << i << ": " << (SOUND ? "ON   " : "OFF  ");
			if (count == 2) cout << i << ": " << HEART << "    ";
			if (count == 3) cout << i;
		}
		count++;
	}
}

// Vẽ Menu khi dừng game
void CGAME::drawPauseMenu(short choice) {
	short count = 0;
	short midHoritonal = Console::getMidHorizontal(),
		midVertical = Console::getMidVertical();
	COORD pos = { midHoritonal - 5, midVertical };
	Console::drawFromFile("Menu/PauseMenuFrame.txt", pos, (int)Color::WHITE);
	for (auto& i : PAUSE_MENU) {
		if (count == choice) {
			Console::setColor(16 * (int)Color::WHITE);
			Console::gotoXY(pos.X + 2, pos.Y + count + 1);
			cout << i;
		}
		else {
			Console::setColor((int)Color::WHITE);
			Console::gotoXY(pos.X + 2, pos.Y + count + 1);
			cout << i;
		}
		count++;
	}
}

// Xóa khung pause menu
void CGAME::clearPauseMenu() {
	// Xoá cái khung
	short midHoritonal = Console::getMidHorizontal(),
		midVertical = Console::getMidVertical();
	COORD pos = { midHoritonal - 5, midVertical };
	for (int i = 0; i < 5; i++) {
		Console::gotoXY(midHoritonal - 5, midVertical + i);
		cout << string(16, ' ');
	}
	// Vẽ lại phần khung bị chồng lên
	Console::drawFromFile("Menu/OverLappingLine.txt", COORD{ (short)(midHoritonal - 5), midVertical }, (int)Color::WHITE);
	// Vẽ lại người nếu nó bị chồng lên
	cn->drawBody();
}

void CGAME::drawSaveMenu()
{
	short count = 0;
	COORD pos = { (short)Border::LEFT + 63, (short)Border::TOP + 15 };
	Console::drawFromFile("Menu/SaveMenuFrame.txt", pos, (int)Color::WHITE);
	string file_name;
	for (short i = 0; i < 4; i++) {
		fstream f;
		file_name = "SaveGame/Data" + to_string(i + 1) + ".txt";

		f.open(file_name);
		if (f) {	// Nếu có lưu ở con số đó: in ra khung màu xanh và cả con số
			Console::drawFromFile("Menu/SaveMenuIcon.txt", COORD{ (short)(pos.X + 2 + i * 7), (short)(pos.Y + 1) }, (int)Color::GREEN);
			Console::gotoXY(pos.X + 4 + i * 7, pos.Y + 2);
			cout << i + 1;
		}
		else {
			Console::drawFromFile("Menu/SaveMenuIcon.txt", COORD{ (short)(pos.X + 2 + i * 7), (short)(pos.Y + 1) }, (int)Color::RED);
			Console::gotoXY(pos.X + 4 + i * 7, pos.Y + 2);
			cout << "X";
		}
		f.close();
	}
}

void CGAME::drawLoadMenu()
{
	short count = 0;
	COORD pos = { (short)Border::LEFT + 63, (short)Border::TOP + 15 };
	Console::drawFromFile("Menu/LoadMenuFrame.txt", pos, (int)Color::WHITE);
	string file_name;
	for (short i = 0; i < 4; i++) {
		fstream f;
		file_name = "SaveGame/Data" + to_string(i + 1) + ".txt";

		f.open(file_name);
		if (f) {	// Nếu có lưu ở con số đó: in ra khung màu xanh và cả con số
			Console::drawFromFile("Menu/SaveMenuIcon.txt", COORD{ (short)(pos.X + 2 + i * 7), (short)(pos.Y + 1) }, (int)Color::GREEN);
			Console::gotoXY(pos.X + 4 + i * 7, pos.Y + 2);
			cout << i + 1;
		}
		else {
			Console::drawFromFile("Menu/SaveMenuIcon.txt", COORD{ (short)(pos.X + 2 + i * 7), (short)(pos.Y + 1) }, (int)Color::RED);
			Console::gotoXY(pos.X + 4 + i * 7, pos.Y + 2);
			cout << "X";
		}
		f.close();
	}
}

void CGAME::clearSaveLoadMenu() {
	Console::drawFromFile("Menu/OverLappingPart.txt", COORD{ (short)Border::LEFT + 63, (short)Border::TOP + 15 }, (int)Color::WHITE);
}

// Game winner -> khi thắng trò chơi
void CGAME::gameWinner() {
	system("cls");
	short midHoritonal = Console::getMidHorizontal(),
		midVertical = Console::getMidVertical();

	COORD pos = { midHoritonal - 25, midVertical - 5 };
	Sleep(400);
	Console::drawFromFile("Menu/Winner.txt", pos, (int)Color::MAGENTA);
	Sleep(400);
	Console::drawFromFile("Menu/Winner.txt", pos, (int)Color::LIGHT_MAGENTA);
	Sleep(400);
	Console::gotoXY(pos.X + 10, pos.Y + 7);
	cout << "Press anything to continue";
	(void)_getch();
}

// Game over -> khi thua trò chơi
void CGAME::gameOver() {
	system("cls");
	short midHoritonal = Console::getMidHorizontal(),
		midVertical = Console::getMidVertical();

	COORD pos = { midHoritonal - 35, midVertical - 5 };
	Sleep(400);
	Console::drawFromFile("Menu/GameOverTitle.txt", pos, (int)Color::MAGENTA);
	Sleep(400);
	Console::drawFromFile("Menu/GameOverTitle.txt", pos, (int)Color::LIGHT_MAGENTA);
	Sleep(400);
	Console::gotoXY(pos.X + 25, pos.Y + 7);
	cout << "Press anything to continue";
	(void)_getch();
}

// Thao tác trên menu chính
short CGAME::runMainMenu(thread* sound) {
	drawTitle();
	short menuChoice = 0;
	thread car(drawMenuCar);
	while (true) {
		carRunning = 0;
		Sleep(100);
		drawMainMenu(menuChoice);
		if (!carRunning) {
			carRunning = 1;
			car.detach();
			car = thread(drawMenuCar);
		}
		char c = toupper(_getch());
		switch (c)
		{
		case (int)Key::UP: case (int)Key::LEFT: case 'W': case 'A':
			menuChoice--;
			if (sound->joinable()) {
				sound->detach();
				*sound = thread(SoundMoveThread);
			}
			if (menuChoice < 0)
				menuChoice = 3;
			break;
		case (int)Key::DOWN: case (int)Key::RIGHT: case 'S': case 'D':
			menuChoice++;
			if (sound->joinable()) {
				sound->detach();
				*sound = thread(SoundMoveThread);
			}
			if (menuChoice > 3)
				menuChoice = 0;
			break;
		case (int)Key::ENTER:
			if (SOUND) {
				PlaySound(L"Sound/Enter.wav", NULL, SND_FILENAME);
			}
			carRunning = 0;
			car.join();
			return menuChoice;
			break;
		default:
			break;
		}
	}
}

// Thao tác trên PauseMenu
short CGAME::runPauseMenu() {
	Sleep(100);             // Tạm dừng để không bị các Mobs vẽ chồng lên menu khi thread chưa kịp dừng
	short menuChoice = 0;
	while (1) {
		drawPauseMenu(menuChoice);
		char c = toupper(_getch());
		switch (c)
		{
		case (int)Key::UP: case (int)Key::LEFT: case 'W': case 'A':
			menuChoice--;
			if (menuChoice < 0)
				menuChoice = 2;
			if (SOUND) {
				PlaySound(L"Sound/Choice.wav", NULL, SND_FILENAME);
			}
			break;
		case (int)Key::DOWN: case (int)Key::RIGHT: case 'S': case 'D':
			menuChoice++;
			if (menuChoice > 2)
				menuChoice = 0;
			if (SOUND) {
				PlaySound(L"Sound/Choice.wav", NULL, SND_FILENAME);
			}
			break;
		case (int)Key::ENTER:
			if (SOUND) {
				PlaySound(L"Sound/Enter.wav", NULL, SND_FILENAME);
			}
			clearPauseMenu();
			return menuChoice;
			break;
		default:
			break;
		}
	}
}

// Thao tác trên setting menu
void CGAME::runSettingMenu() {
	short menuChoice = 0;
	while (1) {
		drawSettingMenu(menuChoice);
		char c = toupper(_getch());
		switch (c)
		{
		case (int)Key::UP: case (int)Key::LEFT: case 'W': case 'A':
			menuChoice--;
			if (menuChoice < 0)
				menuChoice = 3;
			if (SOUND) {
				PlaySound(L"Sound/Choice.wav", NULL, SND_FILENAME);
			}
			break;
		case (int)Key::DOWN: case (int)Key::RIGHT: case 'S': case 'D':
			menuChoice++;
			if (menuChoice > 3)
				menuChoice = 0;
			if (SOUND) {
				PlaySound(L"Sound/Choice.wav", NULL, SND_FILENAME);
			}
			break;
		case (int)Key::ENTER:
			if (SOUND) {
				PlaySound(L"Sound/Enter.wav", NULL, SND_FILENAME);
			}
			switch (menuChoice) {
			case 0:
				THEME = !THEME;
				Console::setColor((int)Color::BLACK);
				system("cls");
				return;
			case 1:
				SOUND = !SOUND;
				break;
			case 2:
				if (HEART == cn->MAX_HEARTS)
					HEART = 1;
				else
					HEART++;
				break;
			case 3:
				cn->setMaxHearts(HEART);
				return;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

// Reset game
void CGAME::resetGame() {
	LEVEL = 1;
	updateLevel();
}

// Bắt đầu game
void CGAME::startGame() {
	resetGame();
	cn->initPeople();
	drawGame();
	pressable = true;
	IS_RUNNING = true;
}

// Thoát game
void CGAME::exitGame(thread* t) {
	IS_RUNNING = false;
	if (t->joinable())
		t->join();
	system("cls");
}

// Dừng game
bool CGAME::pauseGame(thread* t) {
	IS_RUNNING = false;
	int menuChoice = runPauseMenu();
	if (menuChoice == 0) {
		resumeGame(t);
	}
	else if (menuChoice == 1) {
		saveGame(t);
	}
	else {
		exitGame(t);
		return 0;
	}
	return 1;
}

// Tiếp tục game
void CGAME::resumeGame(thread* t) {
	IS_RUNNING = true;
	if (t->joinable()) {
		t->detach();
		*t = thread(SubThread);
	}
}

// Setting
void CGAME::setting() {
	runSettingMenu();
}

bool CGAME::loadGame() {
	pressable = false;
	IS_RUNNING = false;
	Sleep(100);
	drawLoadMenu();
	string file_name;
	ifstream f;
	bool exit = false;
	bool isLoaded = false;
	int value;

	while (!exit) {
		char c = _getch();
		switch (c) {
		case '1': case '2': case '3': case '4':
			f.open("SaveGame/Data" + string(1, c) + ".txt");
			if (f.is_open()) {

				f >> LEVEL >> value;

				cn->setHearts(value);
				cn->resetPosition();
				updateLevel();
				drawGame();
				exit = true;
				isLoaded = true;
			}
			f.close();
			break;

		case 27:
			exit = true;
			break;
		}
	}
	pressable = true;
	return isLoaded;
}

// Load Game
void CGAME::loadGame(thread* t)
{
	loadGame();
	Console::drawFromFile("Menu/OverLappingPart.txt", COORD{ (short)Border::LEFT + 63, (short)Border::TOP + 15 }, (int)Color::WHITE);
	resumeGame(t);
}

void CGAME::saveGame(thread* t)
{
	pressable = false;
	IS_RUNNING = false;
	Sleep(100);
	string file_name;
	ofstream f;
	bool exit = false;
	drawSaveMenu();
	while (!exit) {
		char c = _getch();
		switch (c) {
		case '1': case '2': case '3': case '4':
			f.open("SaveGame/Data" + string(1, c) + ".txt");
			// Lưu level, mạng sống, tốc độ
			f << LEVEL << " " << cn->getHearts();
			f.close();
			exit = true;
			break;
		case 27:
			exit = true;
			break;
		}
	}

	Console::drawFromFile("Menu/OverLappingPart.txt", COORD{ (short)Border::LEFT + 63, (short)Border::TOP + 15 }, (int)Color::WHITE);
	resumeGame(t);
	pressable = true;
}

// Tạo 1 loạt các chướng ngại vật
void CGAME::createMobs(short tt_size, short c_size, short xt_size, short k_size, short xh_size) {
	// trực thăng
	att_size = tt_size;
	createObj(att, att_size, 1, true);

	// chim
	ac_size = c_size;
	createObj(ac, ac_size, 2, false);

	// xe tải
	axt_size = xt_size;
	createObj(axt, axt_size, 3, true);

	// khỉ
	ak_size = k_size;
	createObj(ak, ak_size, 4, false);

	// xe hoi
	axh_size = xh_size;
	createObj(axh, axh_size, 5, true);
}

// Chỉnh độ khó theo level
void CGAME::updateLevel() {
	switch (LEVEL) {
	case 1:
		DELAY = 12;
		createMobs(1, 2, 3, 1, 2);
		break;
	case 2:
		DELAY = 7;
		createMobs(2, 3, 1, 3, 2);
		break;
	case 3:
		DELAY = 7;
		createMobs(2, 4, 2, 3, 2);
		break;
	case 4:
		DELAY = 6;
		createMobs(2, 4, 3, 3, 3);
		break;
	case 5:
		DELAY = 5;
		createMobs(3, 3, 4, 4, 3);
		break;
	case 6:
		DELAY = 5;
		createMobs(3, 4, 4, 4, 3);
		break;
	case 7:
		DELAY = 4;
		createMobs(4, 4, 4, 4, 4);
		break;
	case 8:
		createMobs(4, 4, 4, 5, 3);
		break;
	case 9:
		DELAY = 3;
		createMobs(4, 6, 3, 4, 3);
		break;
	case 10:
		DELAY = 3;
		createMobs(4, 6, 3, 5, 3);
		break;
	case 11:
		DELAY = 2;
		createMobs(4, 4, 4, 5, 4);
		break;
	case 12:
		DELAY = 2;
		createMobs(4, 6, 4, 5, 4);
		break;
	default:
		break;
	}
}

// Update level
void CGAME::upLevel() {
	if (LEVEL < MAX_LEVEL)
		LEVEL++;
}

// Update position người
void CGAME::updatePosPeople(char key, thread* sound) {
	key = toupper(key);
	switch (key) {
	case 'W':
		if (sound->joinable()) {
			sound->detach();
			*sound = thread(SoundMoveThread);
		}
		cn->Up();
		break;
	case 'A':
		if (sound->joinable()) {
			sound->detach();
			*sound = thread(SoundMoveThread);
		}
		cn->Left();
		break;
	case 'S':
		if (sound->joinable()) {
			sound->detach();
			*sound = thread(SoundMoveThread);
		}
		cn->Down();
		break;
	case 'D':
		if (sound->joinable()) {
			sound->detach();
			*sound = thread(SoundMoveThread);
		}
		cn->Right();
		break;
	}
}

// Update position vật
void CGAME::updatePosAnimal() {
	for (int i = 0; i < ac_size; i++) {
		ac[i].move();
	}
	for (int i = 0; i < ak_size; i++) {
		ak[i].move();
	}
}

// Update position xe
void CGAME::updatePosVehical() {
	for (int i = 0; i < att_size; i++) {
		if (light[0].getStatus() == TrafficLight::GREEN) {
			att[i].move();
		}
		else {
			att[i].drawBody();
		}
	}
	for (int i = 0; i < axt_size; i++) {
		if (light[1].getStatus() == TrafficLight::GREEN) {
			axt[i].move();
		}
		else {
			axt[i].drawBody();
		}
	}
	for (int i = 0; i < axh_size; i++) {
		if (light[2].getStatus() == TrafficLight::GREEN) {
			axh[i].move();
		}
		else {
			axh[i].drawBody();
		}
	}
}

// Giảm thời gian đèn giao thông
void CGAME::runTraffic() {
	for (int i = 0; i < light_size; i++)
		light[i].run();
}

bool CGAME::isWin() {
	if (LEVEL >= MAX_LEVEL) {
		return 1;
	}
	else
		return 0;
}

// Âm thanh khi va chạm
void CGAME::soundImpact() {
	if (SOUND) {
		int currentPos = cn->getmY();

		if (currentPos == axh->getmY())
			axh->tell();
		else if (currentPos == axt->getmY())
			axt->tell();
		else if (currentPos == att->getmY())
			att->tell();
		else if (currentPos == ac->getmY())
			ac->tell();
		else if (currentPos == ak->getmY())
			ak->tell();
	}
}
