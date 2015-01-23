#include "ship.h"
#include <cmath>

Ship::Ship(BattleSettings & battleSet, ShipPosition startPosition,
        const char * shipName = "Ship"): rubyShip(shipName),
                                         turnData(rubyShip.getTurnData()),
                                         shipPosition(startPosition),
                                         battleSettings(battleSet),
                                         name(shipName),
                                         speed(0),
                                         acceleration(0) {

    // set ship visual object parameters
    visual = new SceneObjectShip();
    visual -> setPosition(shipPosition.posX, shipPosition.posY);
    visual -> setDirection(
            cos(shipPosition.shipDirection), sin(shipPosition.shipDirection));
    visual -> setCannonDirection(
            cos(shipPosition.cannonDirection), sin(shipPosition.cannonDirection));
    visual -> setRadarDirection(
            cos(shipPosition.radarDirection), sin(shipPosition.radarDirection));

	// set default values
    fireDelay = battleSettings.fireDelay;
    energy = battleSettings.maxEnergy;
	radius = battleSettings.shipRadius;

	// set default values in turnData
	turnData.energy = energy;
    turnData.move = 0;
    turnData.x = shipPosition.posX;
    turnData.y = shipPosition.posY;

    turnData.turn = shipPosition.shipDirection;
    turnData.radar_turn = shipPosition.radarDirection;
    turnData.gun_turn = shipPosition.cannonDirection;

	turnData.max_speed = battleSettings.maxShipSpeed;
	turnData.max_turn_speed = battleSettings.maxTurnSpeed;
	turnData.radar_max_turn_speed = battleSettings.radarMaxTurnSpeed;
	turnData.gun_max_turn_speed = battleSettings.cannonMaxTurnSpeed;

    turnData.fire_power =
            (battleSettings.maxBulletWeight + battleSettings.minBulletWeight)/2;
    turnData.fire = false;
    turnData.fired = false;
    turnData.last_fired_bullet_id = 0;

    rubyShip.run();

}

bool Ship::canShoot() {
	if (!turnData.fire) return false;
	if (fireDelay != 0) return false;
	return (turnData.fire_power >= battleSettings.minBulletWeight &&
        turnData.fire_power <= battleSettings.maxBulletWeight);
}

void Ship::move(unsigned short x, unsigned short y) {
    shipPosition.posX = x;
    shipPosition.posY = y;
}

bool Ship::checkShipCollision (short x, short y) {

}

void Ship::pushPosition() {
    visual -> setPosition(shipPosition.posX, shipPosition.posY);
    visual -> setDirection(
            cos(shipPosition.shipDirection), sin(shipPosition.shipDirection));
    visual -> setCannonDirection(
            cos(shipPosition.cannonDirection), sin(shipPosition.cannonDirection));
    visual -> setRadarDirection(
            cos(shipPosition.radarDirection), sin(shipPosition.radarDirection));

    turnData.x = shipPosition.posX;
    turnData.y = shipPosition.posY;
    turnData.turn = shipPosition.shipDirection;
    turnData.radar_turn = shipPosition.radarDirection;
    turnData.gun_turn = shipPosition.cannonDirection;
    rubyShip.updateTurnData();
}

SceneObjectShip * Ship::getSceneObject() {
    return visual;
}

void Ship::decrementFireDelay() {
        if (fireDelay > 0) --fireDelay;
}

RubyShip & Ship::getRubyShip() {
    return rubyShip;
}

bool Ship::isOnTheScreen(unsigned short x, unsigned short y) {
    return (x <= battleSettings.battlefieldSizeX && x >= 0
        && y <= battleSettings.battlefieldSizeY && y >= 0);
}
