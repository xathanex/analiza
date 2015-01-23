#ifndef ENGINE_H
#define ENGINE_H

#include "ship.h"
#include "battle_settings.h"
#include "bullet.h"
#include "ship_position.h"

#include <vector>
#include <map>


class Engine {
	private:
		std::vector <Ship> ships;
		std::vector <Bullet> bullets;
		BattleSettings battleSettings;
        Scene * scene;
        unsigned nextBulletId;
		
	public:
		Engine(std::vector shipNames);

		// returns true if all ships except one was destroyed
		void moveAndCheckBullets();
		bool executeTurn();
        void destroyBullet();
};

#endif
