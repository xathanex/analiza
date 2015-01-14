#ifndef RUBY_SHIP
#define RUBY_SHIP

#include "ruby_bridge.h"
#include "events.h"
#include "turn_data.h"

class RubyShip
{
public:
	RubyShip(const char*);
	virtual ~RubyShip();

	const char* getName();

	bool onScannedShip(ScannedShipEvent);
	bool onHitByBullet(HitByBulletEvent);
	bool onBulletHit(BulletHitEvent);
	bool onBulletHitBullet(BulletHitBulletEvent);
	bool onShipHit(ShipHitEvent);

	TurnData& getTurnData();
	
	static string rb_class_dir;
	static RubyBridge& bridge;

protected:

	const string getRubyObj();

	const string name;
	rb_value self;
	TurnData td;
};

#endif

