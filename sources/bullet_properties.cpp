#include "bullet_properties.h"

void BulletProperties::getReady() {
    if (speed < maxSpeed)
        speed += 1; // a = 1, v_1 = v_0 + at => v_1 = v_0 + 1
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