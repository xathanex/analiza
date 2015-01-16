#include "ship.h"

Ship::Ship(int x, int y, double angle, BattleSettings battleSettings,
		RubyShip & rShip): Visual(x, y, angle),
						   turret(x, y, angle),
						   radar(x, y, angle),
						   speed(0), acceleration(0){
	// copy object references
	this -> rubyShip = rShip;
	this -> turnData = rubyShip.getTurnData();
	this -> battleSettings = battleSettings;

	// set default values
	this -> energy = battleSettings.maxEnergy;
	this -> fireDelay = battleSettings.fireDelay;
	this -> radius = battleSettings.shipRadius;

	// set default values in turnData
	turnData.energy = energy;
	turnData.fired = false;
	turnData.last_fired_bullet_id = 0;

	// initialize final fields
	turnData.max_speed = battleSettings.maxSpeed;
	turnData.max_turn_speed = battleSettings.maxTurnSpeed;
	turnData.radar_max_turn_speed = battleSettings.radarMaxTurnSpeed;
	turnData.gun_max_turn_speed = battleSettings.gunMaxTurnSpeed;

}

void Ship::shoot(double bulletWeight = 10) {
	
}
