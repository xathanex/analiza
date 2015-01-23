#ifndef BULLET_H
#define BULLET_H

#include "ship.h"

class Bullet {
	private:
		Ship & ship;
		double weight, speed, maxSpeed, dir;
        unsigned short posX, posY;
        unsigned id;

        double tempSpeed, tempPosX, tempPosY;
	
	public:	
		Bullet(Ship & ship, double weight, double maxSpeed,
                unsigned short x, unsigned short y,
                double direction, unsigned id);

		Ship & getShip();
		double getWeight();
        unsigned getId();
        unsigned short getTempX();
        unsigned short getTempY();

        void getReady();
		bool go();

};

#endif
