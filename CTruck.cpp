#include "CTruck.h"

CTRUCK::CTRUCK() : CVEHICLE() {
    Y = mY * TILE_Y + (short)Border::TOP;
}

CTRUCK::~CTRUCK() {

}

void CTRUCK::drawBody() {
    if (direction)
        Console::drawFromFile("Mobs/Truck left.txt", COORD{ X,Y }, (int)Color::CYAN);
    else
        Console::drawFromFile("Mobs/Truck right.txt", COORD{ X,Y }, (int)Color::CYAN);
}

void CTRUCK::tell() {
    if (SOUND) {
        PlaySound(L"Sound/Truck.wav", NULL, SND_FILENAME);
    }
}

void CTRUCK::move() {
    if (direction) {
        if (X < (short)Border::RIGHT - 10) {
            Console::removeSpace(X, Y, true);
            X++;
            drawBody();
        }
        else {
            Console::removeSpace(X, Y, true);
            X = (short)Border::LEFT;
        }
    }
    else {
        if (X > (short)Border::LEFT) {
            Console::removeSpace(X, Y, true);
            X--;
            drawBody();
        }
        else {
            Console::removeSpace(X, Y, true);
            X = (short)Border::RIGHT;
        }
    }
}
