#include "CHelicopter.h"

CHELICOPTER::CHELICOPTER() : CVEHICLE() {
    Y = mY * TILE_Y + (short)Border::TOP;
}

CHELICOPTER::~CHELICOPTER() {

}

void CHELICOPTER::drawBody() {
    if (direction)
        Console::drawFromFile("Mobs/Helicopter left.txt", COORD{ X,Y }, (int)Color::GREEN);
    else
        Console::drawFromFile("Mobs/Helicopter right.txt", COORD{ X,Y }, (int)Color::GREEN);
}

void CHELICOPTER::tell() {
    if (SOUND) {
        PlaySound(L"Sound/Helicopter.wav", NULL, SND_FILENAME);
    }
}

void CHELICOPTER::move() {
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