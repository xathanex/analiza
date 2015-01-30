#ifndef SHIP_H
#define SHIP_H

#include <string>

#include "battle_settings.h"
#include "ruby_ship.h"
#include "turn_data.h"
#include "ship_position.h"
#include "graphics/Scene.h"
#include "graphics/SceneObjects.h"

class Ship {
	private:
        RubyShip rubyShip;
        TurnData & turnData;
        ShipPosition & shipPosition;
        SceneObjectShip * visual;

		std::string name;
        short fireDelay;
		double energy, tempSpeed, speed, acceleration, radius;
		
	public:		
		Ship(ShipPosition startPosition, const char * shipName);
        std::string getName();
		bool canShoot();
		bool checkShipCollision (short x, short y);
        void pushPosition();
        SceneObjectShip * getSceneObject();
        RubyShip & getRubyShip();
        void decrementFireDelay();
        bool isOnTheScreen(unsigned short x, unsigned short y);
        void getReady();
        void go();

};

#endif
