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

        void bulletHitBulletEvent(int i1, int i2);
        void bulletHitShipEvent(int bulletIterator, int shipIterator);
        void shipHitShipEvents(int i1, int i2);

        void checkBulletShipCollision(int bulletIterator, int shipIterator);

        void moveBullets();
        void moveShips();

		void moveAndCheck();
		bool executeTurn();


};

#endif
