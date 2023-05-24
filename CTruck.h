#ifndef _CTRUCK_H
#define _CTRUCK_H

#include "CVehicle.h"

class CTRUCK : public CVEHICLE {
public:
	CTRUCK();
	~CTRUCK();

	// Minh họa
	void drawBody() override;
	void tell() override;
	void move() override;
};

#endif