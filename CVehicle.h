#ifndef _CVEHICLE_H
#define _CVEHICLE_H

#include "Console.h"

class CVEHICLE{
protected:
	short mY;
	short X, Y;										// Tọa độ thực trên console
	bool direction = true;							// Hướng đi (true: trái -> phải, false: phải -> trái)
public:
	CVEHICLE();
	~CVEHICLE();

	// Setter
	void setmY(short row) { mY = row; Y = mY * TILE_Y + (short)Border::TOP; };
	void setX(short x) { X = x; };
	void setDirection(bool d) { direction = d; };

	// Getter
	bool getDirection() const { return direction; };
	short getX() const { return X; };
	short getY() const { return Y; };
	short getmY() const { return mY; };

	// Minh họa
	virtual void drawBody() = 0;					// Hình xe cộ
	virtual void tell() = 0;						// Tiếng kêu của xe cộ
	virtual void move() = 0;						// Di chuyển xe cộ
};

#endif