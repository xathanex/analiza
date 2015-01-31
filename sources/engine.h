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
		Engine(std::vector shipNames);

		// returns true if all ships except one was destroyed
        void moveBullets();
        void moveShips();
        void bulletHitBulletEvents(std::vector <short> & index);
		void moveAndCheck();
		bool executeTurn();
};

#endif
