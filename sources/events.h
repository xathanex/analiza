#ifndef EVENTS_H
#define EVENTS_H

struct ScannedShipEvent
{
	const double bearing, distance, heading, energy;
	const char* name;
	const short speed;
};

struct HitByBulletEvent
{
	const int bullet_id;
};

struct BulletHitEvent
{
	const int bullet_id;
	const char* name;
	const double energy;
};

struct BulletHitBulletEvent
{
	const int bullet_id, bulletHit_id;
};

struct ShipHitEvent
{
	const char* name;
	const double bearing, distance, heading, energy;
};
#endif

