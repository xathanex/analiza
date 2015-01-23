#ifndef BATTLE_SETTINGS_H
#define BATTLE_SETTINGS_H

struct BattleSettings {
    // turn settings
    double maxTurnSpeed, radarMaxTurnSpeed, cannonMaxTurnSpeed,
            maxBulletSpeed;
    unsigned short maxShipSpeed, fireDelay;

    // battlefield settings
    unsigned short battlefieldSizeX, battlefieldSizeY, maxEnergy;
    double shipRadius, minBulletWeight,
            maxBulletWeight; // radius of five circles in ship
};

# endif