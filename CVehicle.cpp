#include "CVehicle.h"

CVEHICLE::CVEHICLE() {
   mY = 0;
   X = (short)Border::LEFT + 1;
   Y = (short)Border::TOP + 1;
   direction = true;
}

CVEHICLE::~CVEHICLE() {

}
