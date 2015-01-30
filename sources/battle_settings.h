#ifndef BATTLE_SETTINGS_H
#define BATTLE_SETTINGS_H

#include <math.h>

namespace BattleSettings {
    // turn settings
    const unsigned short maxShipSpeed = 8;
    const double maxTurnSpeed = M_PI / 8.0;
    const double radarMaxTurnSpeed = M_PI / 8.0;
    const double cannonMaxTurnSpeed = M_PI / 8.0;
    const double maxBulletSpeed = 10.0;
    const unsigned short fireDelay = 15;

    // battlefield settings
    const unsigned short battlefieldSizeX = 800;
    const unsigned short battlefieldSizeY = 600;
    const unsigned short maxEnergy = 100;
    const double minBulletWeight = 1.0;
    const double maxBulletWeight = 20.0;
    const double shipRadius = 7.0;
}

#endif