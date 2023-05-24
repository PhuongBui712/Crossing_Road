#ifndef _CTRAFFIC_H
#define _CTRAFFIC_H

#include "Console.h"

enum class TrafficLight {
	RED = 0,
	YELLOW = 1,
	GREEN = 2
};

class CTRAFFIC {
private:
	TrafficLight status;											// Trạng thái đèn giao thông (xanh, vàng, đỏ)
	short timeRed, timeYellow, timeGreen;							// Thời gian đèn tồn tại
	const short RED_TIME = 15, GREEN_TIME = 65, YELLOW_TIME = 6;	// Thời gian mặc định của đèn
	short X, Y;														// Tọa độ thực trên console
	short mY;														// Vị trí hàng trong khung game
public:
	CTRAFFIC();
	~CTRAFFIC();

	// Setter
	void setStatus(TrafficLight value) { status = value; };
	void setTimeGreen(short value) { timeGreen = value; };
	void setmY(short value) { mY = value; Y = mY * TILE_Y + (short)Border::TOP; };

	// Getter
	TrafficLight getStatus() { return status; };
	short getX() { return X; };
	short getY() { return Y; };
	short getmY() { return mY; };

	void changeStatus();				// Đổi màu đèn
	void run();							// Giảm thời gian đèn

	void drawBody();					// Hình đèn giao thông
};

#endif




