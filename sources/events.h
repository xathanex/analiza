#ifndef EVENTS_H
#define EVENTS_H

struct ScannedShipEvent
{
	const double bearing, heading, energy;
	const unsigned distance;
	const char* name;
	const short speed;
};

struct HitByBulletEvent
{
	const unsigned bullet_id;
};

struct BulletHitEvent
{
	const unsigned bullet_id;
	const char* name;
	const double energy;
};

struct BulletHitBulletEvent
{
	const unsigned bullet_id, bulletHit_id;
};

struct ShipHitEvent
{
	const char* name;
	const double bearing, heading, energy;
	const unsigned distance;
};
#endif

