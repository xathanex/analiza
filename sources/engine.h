#ifndef ENGINE_H
#define ENGINE_H

#include "ship.h"
#include <vector>


class Engine {
	private:
		int numOfShips;
		Ship * ships;
		
	public:
		Engine(int numOfShips);
};

#endif
