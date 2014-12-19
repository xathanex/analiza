#include "ship.h"

int Ship::shipWidth = 10;
int Ship::shipLength = 10;
double Ship::maxHealth = 100;

Ship::Ship(int x, int y, double angle): Visual(x, y, shipWidth, shipLength, angle),
										health(maxHealth), turret(x, y, angle), radar(x, y, angle) {
}

void Ship::shoot(double bulletWeight = 10) {
	
}
