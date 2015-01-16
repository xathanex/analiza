#include "bullet.h"

Bullet::Bullet(Ship & ship, double weight, int x, int y, double angle):
		Visual(x, y, angle), weight(weight) {
	this -> ship = ship;
}

Ship & Bullet::getShip() {
	return ship;
}

double Bullet::getWeight() {
	return weight;
}
