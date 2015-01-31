#include "ship.h"
#include <cmath>

Ship::Ship(ShipProperties startPosition,
        const char * shipName = "Ship"): rubyShip(shipName),
                                         turnData(rubyShip.getTurnData()),
                                         properties(startPosition),
                                         name(shipName),
                                         speed(0) {

    // set ship visual object parameters
    visual = new SceneObjectShip();
    visual -> setPosition((int)properties.posX, (int)properties.posY);
    visual -> setDirection(
            cos(properties.shipDirection), sin(properties.shipDirection));
    visual -> setCannonDirection(
            cos(properties.cannonDirection), sin(properties.cannonDirection));
    visual -> setRadarDirection(
            cos(properties.radarDirection), sin(properties.radarDirection));

	// set default values
    fireDelay = BattleSettings::fireDelay;
    energy = BattleSettings::maxEnergy;

	// set default values in turnData
    turnData.energy = energy;
    turnData.move = 0;
    turnData.x = (unsigned short)properties.posX;
    turnData.y = (unsigned short)properties.posY;

    turnData.turn = properties.shipDirection;
    turnData.radar_turn = properties.radarDirection;
    turnData.gun_turn = properties.cannonDirection;

    turnData.max_speed = (unsigned short)BattleSettings::maxShipSpeed;
    turnData.max_turn_speed = BattleSettings::maxTurnSpeed;
    turnData.radar_max_turn_speed = BattleSettings::radarTurnSpeed;
    turnData.gun_max_turn_speed = BattleSettings::cannonTurnSpeed;

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
    visual -> setPosition(properties.posX, properties.posY);
    visual -> setDirection(
            cos(properties.shipDirection), sin(properties.shipDirection));
    visual -> setCannonDirection(
            cos(properties.cannonDirection), sin(properties.cannonDirection));
    visual -> setRadarDirection(
            cos(properties.radarDirection), sin(properties.radarDirection));

    turnData.x = properties.posX;
    turnData.y = properties.posY;
    turnData.turn = properties.shipDirection;
    turnData.radar_turn = properties.radarDirection;
    turnData.gun_turn = properties.cannonDirection;
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
        properties.posX += cos(properties.shipDirection);
        properties.posX += sin(properties.shipDirection);
        --tempSpeed;
    }
}
