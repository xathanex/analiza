#ifndef BULLET_H
#define BULLET_H

#include "visual.h"
#include "ship.h"

class Bullet : public Visual {
	private:
		static double minWeight;
		static double maxWeight;
		Ship ship;
		double weight;
	
	public:	
		Bullet(Ship ship, double weight, int x, int y, double angle);
		Ship getShip();
		double getWeight();
};

#endif
