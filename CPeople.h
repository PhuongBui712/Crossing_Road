#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "Console.h"
#include "CAnimal.h"
#include "CVehicle.h"

class CPEOPLE {
	short mX, mY;								// Tọa độ theo đơn vị ô
	short X, Y;									// Tọa độ thực trên console
	short hearts;								// Mạng sống còn lại (Nếu hearts = 0 thì chết)
	short maxHearts;							// Mạng sống tối đa người dùng chọn
	bool direction;                             // Hướng người xoay trái hoặc phải ( true quay qua phải, false ngược lại)
public:
	const short MAX_HEARTS = 5;
	CPEOPLE();
	~CPEOPLE();

	// Khởi tạo lại đối tượng
	void initPeople();

	// Cập nhật tọa độ (Setter)
	void setCoordinates(short, short);	// set tọa độ theo đơn vị ô
	void setXY();						// set tọa độ thực
	void setHearts(short);
	void setMaxHearts(short);
	
	// Getter 
	int getX() { return X; };
	int getY() { return Y; };
	int getmY() { return mY; };
	int getmX() { return mX; };
	int getHearts() { return hearts; }
	short getMaxHearts() { return maxHearts; };

	// Cập nhật vị trí 
	void Up();
	void Down();
	void Left();
	void Right();

	// Vẽ
	void drawBody();				// Người chơi
	void drawHeart(short, short);		// Mạng sống còn lại của người chơi
	void drawHeartBroken(short, short);	// Mạng sống đã mất của người chơi	
	void drawHealthBar();				// Thanh mạng sống

	// Reset
	void resetHearts();					// Reset mạng sống
	void resetPosition();				// Reset vị trí

	// Check trạng thái
	bool isFinish();
	bool isDead();
	bool isImpact(const CVEHICLE*, int);
	bool isImpact(const CANIMAL*, int);

	// Khác
	void subHeart();					// Trừ mạng sống đi 1
};
#endif 


