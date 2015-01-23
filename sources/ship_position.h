#ifndef SHIP_POSITION_H
#define SHIP_POSITION_H


struct ShipPosition {
    unsigned short posX, posY;
    double shipDirection, cannonDirection, radarDirection;
};


#endif