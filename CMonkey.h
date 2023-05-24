#ifndef _CMONKEY_H
#define _CMONKEY_H

#include "CAnimal.h"

class CMONKEY : public CANIMAL {
public:
	CMONKEY();
	~CMONKEY();

	// Minh họa
	void drawBody() override;
	void tell() override;	
	void move() override;		
};
#endif 


