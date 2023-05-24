#ifndef _CHELICOPTER_H
#define _CHELICOPTER_H

#include "CVehicle.h"

class CHELICOPTER : public CVEHICLE {
public:
	CHELICOPTER();
	~CHELICOPTER();

	// Minh họa
	void drawBody() override;				
	void tell() override;					
	void move() override;					
};
#endif 



