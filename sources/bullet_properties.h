#ifndef BULLET_PROPERTIES
#define BULLET_PROPERTIES

struct BulletProperties {
    double weight, speed, maxSpeed, dir;
    double tempSpeed, posX, posY;

    void getReady();
    bool go();
};

#endif