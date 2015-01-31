#include "bullet.h"

#include <cmath>

Bullet::Bullet(Ship & ship, double weight, unsigned short x,
        unsigned short y, double direction): ship(ship){
    rubyBullet = new RubyBullet(ship.getName().c_str(), x, y, weight);

    properties.dir = direction;
    properties.weight = weight;
    properties.posX = x;
    properties.posY = y;
}

Ship & Bullet::getShip() {
	return ship;
}

double Bullet::getWeight() {
	return properties.weight;
}

bool Bullet::goAndCheck() {
    if(tempSpeed > 0) {
        // bullet can move
        properties.posX += cos(properties.dir);
        properties.posY += sin(properties.dir);
        --tempSpeed;
        return ship.isOnTheScreen(
                (unsigned short)properties.posX, (unsigned short)properties.posY);
    }
    else return false;
}

unsigned short Bullet::getX() {
    return (unsigned short) properties.posX;
}

unsigned short Bullet::getY() {
    return (unsigned short) properties.posY;
}

unsigned Bullet::getId() {
    return rubyBullet -> getID();
}

void Bullet::pushPosition() {
    visual -> setPosition((unsigned short) properties.posX, (unsigned short) properties.posY);
    visual -> setDirection(
            cos(properties.dir), sin(properties.dir));

    rubyBullet -> setPos((short)properties.posX, (short)properties.posY);

    // getReady
    tempSpeed = BattleSettings::bulletSpeed;
}
