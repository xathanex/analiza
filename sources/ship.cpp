#include "ship.h"
#include <cmath>

Ship::Ship(ShipPosition startPosition,
        const char * shipName = "Ship"): rubyShip(shipName),
                                         turnData(rubyShip.getTurnData()),
                                         shipPosition(startPosition),
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
    fireDelay = BattleSettings::fireDelay;
    energy = BattleSettings::maxEnergy;
	radius = BattleSettings::shipRadius;

	// set default values in turnData
    turnData.energy = energy;
    turnData.move = 0;
    turnData.x = shipPosition.posX;
    turnData.y = shipPosition.posY;

    turnData.turn = shipPosition.shipDirection;
    turnData.radar_turn = shipPosition.radarDirection;
    turnData.gun_turn = shipPosition.cannonDirection;

    turnData.max_speed = BattleSettings::maxShipSpeed;
    turnData.max_turn_speed = BattleSettings::maxTurnSpeed;
    turnData.radar_max_turn_speed = BattleSettings::radarMaxTurnSpeed;
    turnData.gun_max_turn_speed = BattleSettings::cannonMaxTurnSpeed;

    turnData.fire_power =
            (BattleSettings::maxBulletWeight + BattleSettings::minBulletWeight)/2;
    turnData.fire = false;
    turnData.fired = false;
    turnData.last_fired_bullet_id = 0;

    rubyShip.run();
}

std::string Ship::getName() {
    return name;
}


bool Ship::canShoot() {
	if (!turnData.fire) return false;
	if (fireDelay != 0) return false;
	return (turnData.fire_power >= BattleSettings::minBulletWeight &&
        turnData.fire_power <= BattleSettings::maxBulletWeight);
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

    getReady();
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
    return (x <= BattleSettings::battlefieldSizeX && x >= 0
            && y <= BattleSettings::battlefieldSizeY && y >= 0);
}

void Ship::getReady() {
    double tmp = 0;
    double a = BattleSettings::shipAccuracy;
    for (double i = a; i < speed; i += a)
        tmp += i;
    if (turnData.move <= tmp)
        if (speed < a) speed = 0;
        else speed -= a;
    else
        speed += a;
    tempSpeed = speed;
}

void Ship::go() {
    if (tempSpeed > 0) {
        tempPosX += cos(dir);
        tempPosY += sin(dir);
        --tempSpeed;
    }
}
