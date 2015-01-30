#include "bullet_properties.h"

void BulletProperties::getReady() {
    tempSpeed = speed;
}

bool BulletProperties::go() {
    if (tempSpeed > 0) {
        tempPosX += cos(dir);
        tempPosY += sin(dir);
        --tempSpeed;
        return true;
    }
    return false;
}