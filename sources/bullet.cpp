#include "bullet.h"

double Bullet::minWeight = 1;
double Bullet::maxWeight = 10;

Bullet::Bullet(Ship ship, double weight, int x, int y, double angle):
		Visual(x, y, 1, 1, angle), ship(ship) {
	if (weight < minWeight) this -> weight = minWeight;
	else if (weight > maxWeight) this -> weight = maxWeight;
	else this -> weight = weight;
}

Ship Bullet::getShip() {
	return ship;
}

double Bullet::getWeight() {
	return weight;
}
