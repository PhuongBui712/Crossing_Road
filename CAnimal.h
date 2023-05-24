#ifndef _ANIMAL_H
#define _ANIMAL_H

#include "Console.h"

class CANIMAL {
protected:
	short mY;
	short X, Y;										// Tọa độ thực trên console
	bool direction;									// Hướng bay (true: trái -> phải, false: phải -> trái)
public:
	CANIMAL();
	~CANIMAL();
	
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
	virtual void drawBody() = 0;					// Hình động vật
	virtual void tell() = 0;						// Tiếng kêu của con vật
	virtual void move() = 0;						// Di chuyển con vật
};

#endif