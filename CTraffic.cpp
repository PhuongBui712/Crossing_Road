#include "CTraffic.h"

CTRAFFIC::CTRAFFIC() {
	status = TrafficLight::GREEN;
	timeRed = RED_TIME;
	timeYellow = YELLOW_TIME;
	timeGreen = GREEN_TIME;
	mY = 1;
	Y = mY * TILE_Y + (short)Border::TOP;
	X = 5;
}

CTRAFFIC::~CTRAFFIC() {

}

// thay đổi trạng thái của đèn
void CTRAFFIC::changeStatus() {
	if (status == TrafficLight::RED) {
		status = TrafficLight::GREEN;
	}
	else if (status == TrafficLight::GREEN) {
		status = TrafficLight::YELLOW;
	}
	else {
		status = TrafficLight::RED;
	}
}


void CTRAFFIC::drawBody() {
	COORD posLight = { X, (short)(Y + (int)status) };
	Color colorLight;
	if (status == TrafficLight::GREEN) {
		colorLight = Color::GREEN;
	}
	else if (status == TrafficLight::YELLOW) {
		colorLight = Color::YELLOW;
	}
	else {
		colorLight = Color::RED;
	}
	Console::removeSpace(X, Y);
	Console::drawFromFile("Traffic/FrameTraffic.txt", COORD{ (short)(X - 1),(short)(Y - 1) }, (int)Color::WHITE);
	Console::drawFromFile("Traffic/Traffic.txt", posLight, (int)colorLight);
}

void CTRAFFIC::run() {
	if (status == TrafficLight::RED) {
		timeRed--;	
	}
	else if (status == TrafficLight::YELLOW) {
		timeYellow--;
	}
	else {
		timeGreen--;
	}

	if (timeRed == 0 || timeYellow == 0 || timeGreen == 0) {
		changeStatus();
		drawBody();
	}

	if (timeRed == 0) {
		timeRed = RED_TIME;
	}
	else if (timeYellow == 0) {
		timeYellow = YELLOW_TIME;
	}
	else if (timeGreen == 0) {
		timeGreen = GREEN_TIME;
	}
}