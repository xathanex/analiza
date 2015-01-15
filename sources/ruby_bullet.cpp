#include "ruby_bullet.h"

RubyBridge& RubyBullet::bridge = RubyBridge::initialize();

RubyBullet::RubyBullet(const char* owner_name, short x, short y, double power)
{
	char tmp[256] = {};
	sprintf(tmp, "@bullets << Bullet.new(%i, %i, %g,'%s')", x, y, power, owner_name);
	bridge.exec(tmp);
	id = stoi(bridge.exec("@bullets.count"));
}

RubyBullet::~RubyBullet()
{
	char tmp[256] = {};
	sprintf(tmp, "@bullets[%i] = nil", getID());
	bridge.exec(tmp);
}

unsigned RubyBullet::getID() const { return id-1; }
