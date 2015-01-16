#include "ruby_ship.h"

RubyBridge& RubyShip::bridge = RubyBridge::initialize();

RubyShip::RubyShip(const char* class_name): name(class_name)
{
	string cap_name = name;
	cap_name[0] = toupper(cap_name[0]);
	rb_value rb_class = bridge.define_class(name.c_str());
	bridge.exec_file(("ships/"+name+".rb").c_str());
	bridge.exec(("@"+name+" = "+cap_name+".new").c_str());
}

RubyShip::~RubyShip(){}

const char* RubyShip::getName(){ return name.c_str(); }

const string RubyShip::getRubyObj(){ return "@"+name; }

TurnData& RubyShip::getTurnData()
{
	td.energy = stod(bridge.exec(getRubyObj()+".energy"));
	td.x = stoi(bridge.exec(getRubyObj()+".x"));
	td.y = stoi(bridge.exec(getRubyObj()+".y"));
	td.move = stod(bridge.exec(getRubyObj()+".move"));
	td.turn = stod(bridge.exec(getRubyObj()+".turn"));
	td.max_speed = stod(bridge.exec(getRubyObj()+".max_speed"));
	td.max_turn_speed = stod(bridge.exec(getRubyObj()+".max_turn_speed"));
	td.radar_turn = stod(bridge.exec(getRubyObj()+".radar_turn"));
	td.radar_max_turn_speed = stod(bridge.exec(getRubyObj()+".radar_max_turn_speed"));
	td.gun_turn = stod(bridge.exec(getRubyObj()+".gun_turn"));
	td.gun_max_turn_speed = stod(bridge.exec(getRubyObj()+".gun_max_turn_speed"));
	
	string s = bridge.exec(getRubyObj()+".fire_power");
	if(s == "nil"){ td.fire_power = 0; td.fire = false; }
	else { td.fire_power = stod(s); td.fire = true; }
	return td;
}

bool run()
{
	bridge.exec(string(tmp)+"@"+name+".run");
	return bridge.last_exec();	
}

bool RubyShip::onScannedShip(ScannedShipEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bearing: %g, distance: %g, heading: %g, energy: %g, name: \'%s\', speed: %i }\n", e.bearing, e.distance, e.heading, e.energy, e.name, e.speed);
	bridge.exec(string(tmp)+"@"+name+".onScannedShip event");
	return bridge.last_exec();
}

bool RubyShip::onHitByBullet(HitByBulletEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bullet: @bullets[%i] }\n", e.bullet_id);
	bridge.exec(string(tmp)+"@"+name+".onHitByBullet event");
	return bridge.last_exec();
}

bool RubyShip::onBulletHit(BulletHitEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bullet: @bullets[%i] }\n", e.bullet_id);
	bridge.exec(string(tmp)+"@"+name+".onHitByBullet event");
	return bridge.last_exec();
}

bool RubyShip::onBulletHitBullet(BulletHitBulletEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bullet: @bullets[%i], bulletHit: @bullets[%i]}\n", e.bullet_id, e.bulletHit_id);
	bridge.exec(string(tmp)+"@"+name+".onBulletHitBullet event");
	return bridge.last_exec();
}

bool RubyShip::onShipHit(ShipHitEvent e)
{
	char tmp[256] = {};
	sprintf(tmp, "event = { bearing: %g, distance: %g, heading: %g, energy: %g, name: \'%s\' }\n", e.bearing, e.distance, e.heading, e.energy, e.name);
	bridge.exec(string(tmp)+"@"+name+".onShipHit event");	
	return bridge.last_exec();
}

