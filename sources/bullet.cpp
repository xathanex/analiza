#include "bullet.h"

#include <cmath>

Bullet::Bullet(Ship & ship, double weight, double maxSpeed, unsigned short x,
        unsigned short y, double direction, unsigned id): ship(ship),
		weight(weight), speed(0), maxSpeed(maxSpeed),
        posX(x), posY(y), dir(direction), id(id) {
}

Ship & Bullet::getShip() {
	return ship;
}

double Bullet::getWeight() {
	return weight;
}

void Bullet::getReady() {
    if (speed < maxSpeed) {
        speed += 1;
        tempSpeed = speed;
        tempPosX = (double)posX;
        tempPosY = (double)posY;
    }
}

bool Bullet::go() {
    if (speed > 0) {
        tempPosX += cos(dir);
        tempPosY += sin(dir);
        --speed;
        return ship.isOnTheScreen(
                (unsigned short)tempPosX, (unsigned short)tempPosY);
    }
}

unsigned short Bullet::getTempX() {
    return (unsigned short) tempPosX;
}

unsigned short Bullet::getTempY() {
    return (unsigned short) tempPosY;
}

unsigned Bullet::getId() {
    return id;
}
