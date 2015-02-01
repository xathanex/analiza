#include "engine.h"
#include "events.h"

#include <cmath>
#include <vector>

Engine::Engine(std::vector<const char *> shipNames) {
    // sets start positions for all ships
    // TODO: randomowe pozycje statków
    // TODO: wykrywanie kolizji pozycji statków

    /*
    ShipProperties shipPos1, shipPos2;

    shipPos1.posX = BattleSettings::battlefieldSizeX / 4;
    shipPos1.posY = BattleSettings::battlefieldSizeY / 2;
    shipPos2.posX = BattleSettings::battlefieldSizeX -
            (BattleSettings::battlefieldSizeX / 4);
    shipPos2.posY = BattleSettings::battlefieldSizeY / 2;

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
    */

}

void Engine::bulletHitBulletEvent(int i1, int i2) {
    BulletHitBulletEvent e1 {
            bullets[i1] -> getId(),
            bullets[i2] -> getId()
    };
    bullets[i1] -> getShip().getRubyShip().onBulletHitBullet(e1);

    BulletHitBulletEvent e2 {
            bullets[i2] -> getId(),
            bullets[i1] -> getId()
    };
    bullets[i2] -> getShip().getRubyShip().onBulletHitBullet(e2);

    bullets.erase(bullets.begin() + i1);
    bullets.erase(bullets.begin() + i2);
}

void Engine::shipHitShipEvents(int i1, int i2) {
    ShipHitEvent e1 {
            ships[i2] -> getName(),
            ships[i2] -> getDirection(),
            atan2(ships[i2] -> getY(), ships[i2] -> getX()) - ships[i2] -> getDirection(),
            ships[i2] -> getEnergy(),
            0 // distance between two balls-like ships?
    };
    ships[i1] -> getRubyShip().onShipHit(e1);

    ShipHitEvent e2 {
            ships[i1] -> getName(),
            ships[i1] -> getDirection(),
            atan2(ships[i1] -> getY(), ships[i1] -> getX()) - ships[i1] -> getDirection(),
            ships[i1] -> getEnergy(),
            0 // distance between two balls-like ships?
    };
    ships[i2] -> getRubyShip().onShipHit(e2);
}

void Engine::bulletHitShipEvent(int bulletIterator, int shipIterator) {
    BulletHitEvent be {
            bullets[bulletIterator] -> getId(),
            ships[shipIterator] -> getName(),
            ships[shipIterator] -> getEnergy() - bullets[bulletIterator] -> getWeight()
    };
    bullets[bulletIterator] -> getShip().getRubyShip().onBulletHit(be);

    HitByBulletEvent se {
            bullets[bulletIterator] -> getId()
    };
    ships[shipIterator] -> getRubyShip().onHitByBullet(se);
}

void Engine::checkBulletShipCollision(int bulletIterator, int shipIterator) {
    double bx, by, sx, sy;
    bx = bullets[bulletIterator] -> getX();
    by = bullets[bulletIterator] -> getY();
    sx = ships[shipIterator] -> getX();
    sy = ships[shipIterator] -> getY();
    if (abs(bx - sx) <= BattleSettings::shipRadius &&
            abs(by - sy) <= BattleSettings::shipRadius) {
        bulletHitShipEvent(bulletIterator, shipIterator);
        if (ships[shipIterator] -> decrementEnergy(
                bullets[bulletIterator] -> getWeight())) {
            ships.erase(ships.begin() + shipIterator);
        }
        bullets.erase(bullets.begin() + bulletIterator);
    }



}

void Engine::moveBullets() {
    unsigned short it = 0;
    while (it < bullets.size()) {
        if (!bullets[it] -> goAndCheck()) {
            // bullet is outside the screen
            bullets.erase(bullets.begin() + it);
            continue;
        }
        for (int k = 0; k < bullets.size(); ++k) {
            if (bullets[it] -> getX() == bullets[k] -> getX() &&
                    bullets[it] -> getY() == bullets[k] -> getY()) {
                bulletHitBulletEvent(it, k);
                break;
            }
        }
        ++it;
    }
}

void Engine::moveShips() {
    int  it = 0;
    while (it < ships.size()) {
        ships[it] -> go();

        // check if moved ship does not cover another ships
        for (int j = 0; j < ships.size(); ++j) {
            if (ships[it] ->isShipCollision(ships[j] -> getX(), ships[j] -> getY())) {
                shipHitShipEvents(it, j);
                ships[it] -> undoMove();
                break;
            }
        }
        ++it;
    }
}

void Engine::moveAndCheck() {
    short time, it, sh, b;
    for (time = 0; time < BattleSettings::bulletSpeed; ++time) {
        moveBullets();
        moveShips();
        for (sh = 0; sh < ships.size(); ++sh) {
            for (b = 0; b < bullets.size(); ++b) {
                checkBulletShipCollision(b, sh);
            }
        }
    }

}

void Engine::shoot() {
    for (int i = 0; i < ships.size(); ++i) {
        if (ships[i] -> canShoot()) {
            // TODO: builder do tworzenia pocisków
            // bullets.push_back(new Bullet(ships[i], ))
        }

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
    if (ships.size() < 2) return false;

    // performs shoot
    shoot();

    // performs scan


    return true;
}
