#ifndef _CCAR_H
#define _CCAR_H

#include "CVehicle.h"

class CCAR : public CVEHICLE {
public:
	CCAR();
	~CCAR();

	// Minh họa
	void drawBody() override;				
	void tell() override;					
	void move() override;				
};

#endif 




