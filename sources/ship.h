#ifndef SHIP_H
#define SHIP_H

#include "visual.h"
#include "turret.h"
#include "radar.h"

class Ship: public Visual {
	private:
		static int shipWidth;
		static int shipLength;
		static double maxHealth;
		Turret turret;
		Radar radar;
		
		double health;
		
	public:		
		Ship(int x, int y, double angle);
		void shoot(double bulletWeight);
};

#endif
