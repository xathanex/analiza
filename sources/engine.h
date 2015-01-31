#ifndef ENGINE_H
#define ENGINE_H

#include "ship.h"
#include "battle_settings.h"
#include "bullet.h"
#include "ship_properties.h"

#include <vector>
#include <map>


class Engine {
	private:
		std::vector <Ship*> ships;
		std::vector <Bullet*> bullets;
        Scene * scene;
		
	public:
		Engine(std::vector<const char *> shipNames);

		// returns true if all ships except one was destroyed
        void moveBullets();
        void moveShips();
        void bulletHitBulletEvent(int i1, int i2);
        void bulletHitShipEvent(int bulletIterator, int shipIterator);
        void shipHitShipEvents(int i1, int i2);
		void moveAndCheck();
		bool executeTurn();

        void checkBulletShipCollision(int bulletIterator, int shipIterator);
};

#endif
