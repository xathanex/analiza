#ifndef SHIP_H
#define SHIP_H

#include <string>

#include "battle_settings.h"
#include "ruby_ship.h"
#include "turn_data.h"
#include "ship_properties.h"
#include "graphics/Scene.h"
#include "graphics/SceneObjects.h"

class Ship {
	private:
        RubyShip rubyShip;
        TurnData & turnData;
        ShipProperties & properties;
        SceneObjectShip * visual;

		const char * name;
        short fireDelay;
		double energy, tempSpeed, speed;
		
	public:		
		Ship(ShipProperties startPosition, const char * shipName);

		bool canShoot();
		bool isShipCollision (double x, double y);
        bool isOnTheScreen();

        void decrementFireDelay();
        bool decrementEnergy(double value);

        void getReady();
        void go();
        void undoMove();
        void pushPosition();

        SceneObjectShip * getSceneObject();
        RubyShip & getRubyShip();
        const char * getName();
        double getX();
        double getY();
        double getEnergy();
        double getDirection();
};

#endif
