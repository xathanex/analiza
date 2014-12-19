#include "visual.h"

Visual::Visual(int x, int y, int sizeX, int sizeY, double angle) : 
		x(x), y(y), sizeX(sizeX), sizeY(sizeY), angle(angle) {};

int Visual::getX() {
	return x;
}

int Visual::getY() {
	return y;
}

int Visual::getSizeX() {
	return sizeX;
}

int Visual::getSizeY() {
	return sizeY;
}

double Visual::getAngle() {
	return angle;
}

void Visual::rotate(double a) {
	angle = a;
	// tutaj akcja związana z rotate
}
