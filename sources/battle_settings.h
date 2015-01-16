#ifndef BATTLE_SETTINGS_H
#define BATTLE_SETTINGS_H

struct BattleSettings {
    // turn settings
    double maxSpeed, maxTurnSpeed, radarMaxTurnSpeed, gunMaxTurnSpeed,
            maxAcceleration, maxDeceleration;
    int fireDelay;

    // battlefield settings
    int battlefieldSizeX, battlefieldSizeY, maxEnergy,
            minBulletWeight, maxBulletWeight;
    double shipRadius;
};

# endif