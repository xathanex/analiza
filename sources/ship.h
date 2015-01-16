#ifndef SHIP_H
#define SHIP_H

#include "visual.h"
#include "turret.h"
#include "radar.h"
#include "turn_data.h"
#include "battle_settings.h"
#include "ruby_ship.h"

class Ship: public Visual {
	private:
		Turret turret;
		Radar radar;
		RubyShip & rubyShip;
		TurnData & turnData;
		BattleSettings & battleSettings;

		const double radius;
		double energy, speed, acceleration;
		int fireDelay;
		
	public:		
		Ship(int x, int y, double angle, BattleSettings battleSettings,
				RubyShip & rShip);
		void shoot(double bulletWeight);
};

#endif
