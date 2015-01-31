#ifndef BULLET_H
#define BULLET_H

#include "ship.h"
#include "graphics/SceneObjects.h"
#include "ruby_bullet.h"
#include "bullet_properties.h"

class Bullet {
	private:
        RubyBullet * rubyBullet;
        SceneObjectProjectile * visual;
		Ship & ship;
        BulletProperties properties;

        double tempSpeed;


	public:	
		Bullet(Ship & ship, double weight,
                unsigned short x, unsigned short y,
                double direction);

        bool isOnTheScreen(double x, double y);
		bool goAndCheck();
        void pushPosition();

        Ship & getShip();
        double getWeight();
        unsigned getId();
        unsigned short getX();
        unsigned short getY();

};

#endif
