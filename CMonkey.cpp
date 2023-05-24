#include"CMonkey.h"

CMONKEY::CMONKEY() :CANIMAL() {
    Y = mY * TILE_Y + (short)Border::TOP + 1;
}

CMONKEY::~CMONKEY() {

}

void CMONKEY::drawBody() {
    if (direction)
        Console::drawFromFile("Mobs/Monkey left.txt", COORD{ X,Y }, (int)Color::YELLOW);
    else
        Console::drawFromFile("Mobs/Monkey right.txt", COORD{ X,Y }, (int)Color::YELLOW);
}

void CMONKEY::tell() {
    if (SOUND) {
        PlaySound(L"Sound/Monkey.wav", NULL, SND_FILENAME);
    }
}

void CMONKEY::move() {
    if (direction) {
        if (X < (short)Border::RIGHT) {
            Console::removeSpace(X, Y);
            X++;
            drawBody();
        }
        else {
            Console::removeSpace(X, Y);
            X = (short)Border::LEFT;
        }
    }
    else {
        if (X > (short)Border::LEFT) {
            Console::removeSpace(X, Y);
            X--;
            drawBody();
        }
        else {
            Console::removeSpace(X, Y);
            X = (short)Border::RIGHT;
        }
    }
}