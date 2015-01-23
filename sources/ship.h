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
        ShipPosition shipPosition;
        BattleSettings & battleSettings;
        SceneObjectShip * visual;

		std::string name;
        short fireDelay;
		double energy, speed, acceleration, radius;
		
	public:		
		Ship(BattleSettings & battleSettings, ShipPosition startPosition,
                const char * shipName);
		bool canShoot();
		void move(unsigned short x, unsigned short y);
		bool checkShipCollision (short x, short y);
        void pushPosition();
        SceneObjectShip * getSceneObject();
        RubyShip & getRubyShip();
        void decrementFireDelay();
        bool isOnTheScreen(unsigned short x, unsigned short y);

};

#endif
