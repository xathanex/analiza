#ifndef BATTLE_SETTINGS_H
#define BATTLE_SETTINGS_H

#include <math.h>

namespace BattleSettings {
    // turn settings
    const double maxShipSpeed = 8.0;
    const double maxTurnSpeed = M_PI / 8.0;
    const double radarTurnSpeed = M_PI / 8.0;
    const double cannonTurnSpeed = M_PI / 8.0;
    const double bulletSpeed = 10.0;
    const double shipAccuracy = 0.5;
    const unsigned short fireDelay = 30;

    // battlefield settings
    const unsigned short battlefieldSizeX = 800;
    const unsigned short battlefieldSizeY = 800;
    const unsigned short maxEnergy = 100;
    const double minBulletWeight = 1.0;
    const double maxBulletWeight = 20.0;
    const double shipRadius = 20.0;
}

#endif