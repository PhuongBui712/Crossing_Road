#include "CGame.h"

char MOVING;
CGAME cg;
bool THEME = 1, SOUND = 1;

int main() {
	thread sound(SoundThread);
	while (1) {
		int menuChoice = cg.runMainMenu(&sound);

		if (menuChoice == 0) {
			cg.startGame();
			thread t1(SubThread);
			int key;
			while (1) {
				key = toupper(_getch());
				if(!cg.getPeople()->isDead() && !cg.isWin()){

					if (key == 27) {
						cg.exitGame(&t1);
						break;
					}
					else if (key == 'P') {
						if (!cg.pauseGame(&t1)) {
							break;
						}
					}
					else if (key == 'L')
						cg.saveGame(&t1);
					else if (key == 'T')
						cg.loadGame(&t1);
					else if (cg.IS_RUNNING)
						if (!cg.pressable)
							MOVING = ' ';
						else
							MOVING = key;
				}
				else {
					cg.exitGame(&t1);
					system("cls");
					break;
				}
			}
		}
		else if (menuChoice == 1) {
			if (cg.loadGame()) {
				cg.IS_RUNNING = true;

				thread t1(SubThread);
				int key;

				while (1) {
					key = toupper(_getch());
					if (!cg.getPeople()->isDead() && !cg.isWin()) {

						if (key == 27) {
							cg.exitGame(&t1);
							break;
						}
						else if (key == 'P') {
							if (!cg.pauseGame(&t1)) {
								break;
							}
						}
						else if (key == 'L')
							cg.saveGame(&t1);
						else if (key == 'T')
							cg.loadGame(&t1);
						else if (cg.IS_RUNNING)
							if (!cg.pressable)
								MOVING = ' ';
							else
								MOVING = key;
					}
					else {
						cg.exitGame(&t1);
						system("cls");
						break;
					}
				}
			}
			else {
				system("cls");
			}
		}
		else if (menuChoice == 2) {
			cg.setting();
		}
		else
			break;
	}
	sound.join();
	return 0;
}

void SubThread() {
	short delay_running = cg.getDelay();

	thread sound(SoundThread);
	while (cg.IS_RUNNING) {
		cg.pressable = true;

		// Cập nhật vị trí người chơi
		if (!cg.getPeople()->isDead()) {
			cg.updatePosPeople(MOVING, &sound);
		}
		MOVING = ' ';
		Sleep(10);
		delay_running--;

		cg.checkImpact = 0;

				if (delay_running == 0) {
			cg.runTraffic();
			cg.updatePosVehical();
			cg.updatePosAnimal();
			delay_running = cg.getDelay();
		}
		// Kiểm tra va chạm
		if (cg.getPeople()->isImpact(cg.getCar(), cg.getCarSize())
			|| cg.getPeople()->isImpact(cg.getTruck(), cg.getTruckSize())
			|| cg.getPeople()->isImpact(cg.getHelicopter(), cg.getHelicopterSize())
			|| cg.getPeople()->isImpact(cg.getBird(), cg.getBirdSize())
			|| cg.getPeople()->isImpact(cg.getMonkey(), cg.getMonkeySize())
			)
		{
			cg.checkImpact = 1;
			cg.getPeople()->subHeart();
			cg.getPeople()->drawHealthBar();
			cg.pressable = false;	// Ngưng nhận phím
			cg.soundImpact();
			cg.getPeople()->resetPosition();
			cg.pressable = true;	// Tiếp tục nhận phím
		}
		//Kiểm tra đến đích 
		if (cg.getPeople()->isFinish()) {
			// Tăng level
			cg.upLevel();
			// Hiệu ứng chuyển level
			cg.pressable = false;
			if (!cg.isWin()) {
				if (sound.joinable()) {
					sound.detach();
					sound = thread(SoundUpLevelThread);
				}
				cg.drawTime();
				// Chỉnh độ khó theo level
				cg.updateLevel();
				delay_running = cg.getDelay();
				cg.getPeople()->resetPosition();
				// Vẽ level
				cg.drawLevel();
			}
			cg.pressable = true;
		}

		if (cg.getPeople()->isDead()) {
			cg.pressable = false;
			if (sound.joinable()) {
				sound.detach();
				sound = thread(SoundGameOverThread);
			}
			cg.gameOver();
			cg.pressable = true;
			break;
		}

		if (cg.isWin()) {
			cg.pressable = false;
			if (sound.joinable()) {
				sound.detach();
				sound = thread(SoundWinThread);
			}
			cg.gameWinner();
			cg.pressable = true;
			break;
		}
	}
	sound.join();
}

void SoundThread() {

}

void SoundMoveThread() {
	if (SOUND) {
		PlaySound(L"Sound/Choice.wav", NULL, SND_FILENAME);
	}
}

void SoundGameOverThread() {
	if (SOUND) {
		PlaySound(L"Sound/GameOver.wav", NULL, SND_FILENAME);
	}
}

void SoundUpLevelThread() {
	if (SOUND) {
		PlaySound(L"Sound/UpLevel.wav", NULL, SND_FILENAME);
	}
}

void SoundWinThread() {
	if (SOUND) {
		PlaySound(L"Sound/Win.wav", NULL, SND_FILENAME);
	}
}
