#include "engine.h"
#include "events.h"


#include <cmath>
#include <vector>

Engine::Engine(std::vector<const char *> shipNames): {

    nextBulletId = 0;

    // turn settings
    battleSettings.maxShipSpeed = 8;
    battleSettings.maxTurnSpeed = M_PI / 8.0;
    battleSettings.radarMaxTurnSpeed = M_PI / 8.0;
    battleSettings.cannonMaxTurnSpeed = M_PI / 8.0;
    battleSettings.maxBulletSpeed = 10.0;
    battleSettings.fireDelay = 15;

    // battlefield settings
    battleSettings.battlefieldSizeX = 800;
    battleSettings.battlefieldSizeY = 600;
    battleSettings.maxEnergy = 100;
    battleSettings.minBulletWeight = 1;
    battleSettings.maxBulletWeight = 20;
    battleSettings.shipRadius = 7.0;


    // sets start positions for all ships
    ShipPosition shipPos1, shipPos2;

    shipPos1.posX = battleSettings.battlefieldSizeX / (unsigned short)4;
    shipPos1.posY = battleSettings.battlefieldSizeY / (unsigned short)2;
    shipPos2.posX = battleSettings.battlefieldSizeX -
            (battleSettings.battlefieldSizeX / (unsigned short)4);
    shipPos2.posY = battleSettings.battlefieldSizeY / (unsigned short)2;

    shipPos1.shipDirection = 0.0;
    shipPos1.cannonDirection = 0.0;
    shipPos1.radarDirection = 0.0;
    shipPos2.shipDirection = M_PI;
    shipPos2.cannonDirection = M_PI;
    shipPos2.radarDirection = M_PI;

    Ship tempShip1(battleSettings, shipPos1, shipNames[0]);
    ships.push_back(tempShip1);
    Ship tempShip2(battleSettings, shipPos2, shipNames[1]);
    ships.push_back(tempShip2);

    scene = new Scene();
    scene -> registerSceneObject(ships[0].getSceneObject());
    scene -> registerSceneObject(ships[1].getSceneObject());

}

void Engine::moveAndCheckBullets() {
    std::vector <short> destroyedByBullet;
    std::vector <short> destroyedByShip;
    std::vector <short> destroyedByScreenBorder;
    short temp1, temp2;

    short it, j, k;
    for (it = 0; it < bullets.size(); ++it) {
        bullets[it].getReady();
    }
    for (it = 0; it < battleSettings.maxBulletSpeed; ++it) {
        for (j = 0; j < bullets.size(); ++j) {
            if (!bullets[j].go())
                destroyedByScreenBorder.push_back(j);
        }
        for (j = 0; j < bullets.size(); ++j) {
            for (k = 0; k < bullets.size(); ++k) {
                if (j != k && bullets[j].getTempX() == bullets[k].getTempX() &&
                        bullets[j].getTempY() == bullets[k].getTempY()) {
                    destroyedByBullet.push_back(j);
                    destroyedByBullet.push_back(k);
                    break;
                }
            }
        }
        if (destroyedByBullet.size() > 0) {
            for (j = 0; j < destroyedByBullet.size(); j = j + (short)2) {
                temp1 = destroyedByBullet[j];
                temp2 = destroyedByBullet[j + 1];
                BulletHitBulletEvent e1 {
                        bullets[temp1].getId(),
                        bullets[temp2].getId()
                };
                bullets[temp1].getShip().getRubyShip().onBulletHitBullet(e1);
                BulletHitBulletEvent e2 {
                        bullets[temp2].getId(),
                        bullets[temp1].getId()
                };
                bullets[temp2].getShip().getRubyShip().onBulletHitBullet(e2);
                bullets.erase(bullets.begin() + temp1);
                bullets.erase(bullets.begin() + temp2);
            }
            destroyedByBullet.clear();
        }
        if (destroyedByScreenBorder.size() > 0) {
            for (j = 0; j < destroyedByScreenBorder.size(); ++j)
                bullets.erase(bullets.begin() + destroyedByScreenBorder[j]);
        }
    }

}

bool Engine::executeTurn() {
    /*
    TODO: zaimplementować wykonywanie się tury
    Kolejność wykonywania się elementów:
    1. Battle view is (re)painted.
    2. All robots execute their code until they take action
    (and then paused).
    3. Time is updated (time = time + 1).
    4. All bullets move and check for collisions.
    This includes firing bullets.
    5. All robots move (gun, radar, heading, acceleration,
    velocity, distance, in that order).
    6. All robots perform scans (and collect team messages).
    7. All robots are resumed to take new action.
    8. Each robot processes its event queue.
    */

    // 1. 2. 3.
    int i;
    for (i = 0; i < ships.size(); ++i) {
        ships[i].pushPosition();
        ships[i].decrementFireDelay();
    }

    // 4.
    moveAndCheckBullets();

    // 5.

    // 6.

    // 7.

    // 8.
}