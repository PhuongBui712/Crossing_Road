#ifndef _CBIRD_H
#define _CBIRD_H

#include "CAnimal.h"

class CBIRD : public CANIMAL {
public:
	CBIRD();
	~CBIRD();

	// Minh họa
	void drawBody() override;				
	void tell() override;				
	void move() override;					
};
#endif 
