#ifndef EVENTS_H
#define EVENTS_H

#include "bullet.h"

struct ScannedShipEvent
{
	const double bearing, distance, heading, energy;
	const char* name;
	const short speed;
};

struct HitByBulletEvent
{
	const Bullet bullet;
};

struct BulletHitEvent
{
	const Bullet bullet;
	const char* name;
	const double energy;
};

struct BulletHitBulletEvent
{
	const Bullet bullet, bulletHit;
};

struct ShipHitEvent
{
	const char* name;
	const double bearing, distance, heading, energy;
};
#endif

