#include "engine.h"
#include "events.h"

#include <cmath>
#include <vector>

Engine::Engine(std::vector<const char *> shipNames): {
    // sets start positions for all ships
    // TODO: randomowe pozycje statków
    // TODO: wykrywanie kolizji pozycji statków
    ShipPosition shipPos1, shipPos2;

    shipPos1.posX = BattleSettings::battlefieldSizeX / (unsigned short)4;
    shipPos1.posY = BattleSettings::battlefieldSizeY / (unsigned short)2;
    shipPos2.posX = BattleSettings::battlefieldSizeX -
            (BattleSettings::battlefieldSizeX / (unsigned short)4);
    shipPos2.posY = BattleSettings::battlefieldSizeY / (unsigned short)2;

    shipPos1.shipDirection = 0.0;
    shipPos1.cannonDirection = 0.0;
    shipPos1.radarDirection = 0.0;
    shipPos2.shipDirection = M_PI;
    shipPos2.cannonDirection = M_PI;
    shipPos2.radarDirection = M_PI;

    Ship * tempShip1 = new Ship(shipPos1, shipNames[0]);
    ships.push_back(tempShip1);
    Ship * tempShip2 = new Ship(shipPos2, shipNames[1]);
    ships.push_back(tempShip2);

    scene = new Scene();
    scene -> registerSceneObject(ships[0] -> getSceneObject());
    scene -> registerSceneObject(ships[1] -> getSceneObject());

}
void Engine::moveBullets() {
    unsigned short it = 0;
    while (it < bullets.size()) {
        if (!bullets[it] -> goAndCheck())
            // bullet is outside the screen
            bullets.erase(bullets.begin() + it);
        else
            ++it;
    }
}

void Engine::moveShips() {
    unsigned short it = 0;
    while (it < ships.size()) {
        ships[it] -> go();
    }
}

void Engine::moveAndCheck() {
    std::vector <short> destroyedByBullet;
    std::vector <short> destroyedByShip;
    short temp1, temp2;

    short time, it, k;
    for (time = 0; time < BattleSettings::maxBulletSpeed; ++time) {
        moveBullets();
        moveShips();
        for (it = 0; it < bullets.size(); ++it) {
            for (k = it + (short)1; k < bullets.size(); ++k) {
                if (bullets[it] -> getX() == bullets[k] -> getX() &&
                        bullets[it] -> getY() == bullets[k] -> getY()) {
                    destroyedByBullet.push_back(it);
                    destroyedByBullet.push_back(k);
                    break;
                }
            }
        }
        if (destroyedByBullet.size() > 0) {
            for (it = 0; it < destroyedByBullet.size(); it = it + (short)2) {
                temp1 = destroyedByBullet[it];
                temp2 = destroyedByBullet[it + 1];
                BulletHitBulletEvent e1 {
                        bullets[temp1] -> getId(),
                        bullets[temp2] -> getId()
                };
                bullets[temp1] -> getShip().getRubyShip().onBulletHitBullet(e1);
                BulletHitBulletEvent e2 {
                        bullets[temp2] -> getId(),
                        bullets[temp1] -> getId()
                };
                bullets[temp2] -> getShip().getRubyShip().onBulletHitBullet(e2);
                bullets.erase(bullets.begin() + temp1);
                bullets.erase(bullets.begin() + temp2);
            }
            destroyedByBullet.clear();
        }
        /* źle! statki muszą poruszać się w tym samym czasie co pociski!
        for (it = 0; it < bullets.size(); ++it) {
            for (k = 0; k < ships.size(); ++k) {
                if (ships[k].checkShipCollision(bullets[it].get, bullets[it])){
                    destroyedByBullet.push_back(it);
                    destroyedByBullet.push_back(k);
                    break;
                }
            }
        }
        */
    }

}

bool Engine::executeTurn() {
    /*
    TODO: zaimplementować wykonywanie się tury
    true: go to next turn
    false: game over
    */

    // repaints objects on screen and prepares them to next turn
    // also executes ruby code
    int i;
    for (i = 0; i < ships.size(); ++i) {
        ships[i] -> pushPosition();
        ships[i] -> decrementFireDelay();
    }
    for (i = 0; i < bullets.size(); ++i) {
        bullets[i] -> pushPosition();
    }

    // moves all visible objects and checks for collisions
    moveAndCheck();

    // performs scan


    return true;
}