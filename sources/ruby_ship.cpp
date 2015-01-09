#include <cstdio>
#include "ruby_ship.h"

string RubyShip::rb_class_dir = "ships/";

RubyBridge& RubyShip::bridge = RubyBridge::initialize();

RubyShip::RubyShip(const char* class_name): name(class_name)
{
	string cap_name = name;
	cap_name[0] = toupper(cap_name[0]);
	rb_value rb_class = bridge.define_class(name.c_str());
	bridge.exec_file((rb_class_dir+name+".rb").c_str());
	bridge.exec(("@"+name+" = "+cap_name+".new").c_str());
}

RubyShip::~RubyShip(){}

const char* RubyShip::getName(){ return name.c_str(); }

bool RubyShip::onScannedShip(ScannedShipEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bearing: %g, distance: %g, heading: %g, energy: %g, name: \'%s\', speed: %i }\n", e.bearing, e.distance, e.heading, e.energy, e.name, e.speed);
	bridge.exec(tmp+"@"+name+".onScannedShip event");
	return bridge.last_exec();
}

bool RubyShip::onHitByBullet(HitByBulletEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bullet: Bullet.new(%g, \'%s\') }\n", e.bullet.getWeight(), e.bullet.getShip().getName());
	bridge.exec(tmp+"@"+name+".onHitByBullet event");
	return bridge.last_exec();
}

bool RubyShip::onBulletHit(BulletHitEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bullet: Bullet.new(%g, \'%s\'),  }\n", e.bullet.getWeight(), e.bullet.getShip().getName());
	bridge.exec(tmp+"@"+name+".onHitByBullet event");
	return bridge.last_exec();
}

bool RubyShip::onBulletHitBullet(BulletHitBulletEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bearing: %g, distance: %g, heading: %g, energy: %g, name: \'%s\', speed: %i }\n", e.bearing, e.distance, e.heading, e.energy, e.name, e.speed);
	bridge.exec(tmp+"@"+name+".onBulletHitBullet event");
	return bridge.last_exec();
}

bool RubyShip::onShipHit(ShipHitEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bearing: %g, distance: %g, heading: %g, energy: %g, name: \'%s\' }\n", e.bearing, e.distance, e.heading, e.energy, e.name);
	bridge.exec(tmp+"@"+name+".onShipHit event");	
	return bridge.last_exec();
}

