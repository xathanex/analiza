#include <cassert>
#include "../sources/ruby_ship.h"
#include "../sources/ruby_bullet.h"

using namespace std;

void getTurnData_test()
{
	RubyShip rs("testclass");
	TurnData td = rs.getTurnData();
	assert(td.energy == 100);
	assert(td.move == 0);
	assert(td.turn == 0);
	assert(td.max_speed == 8);
	assert(td.max_turn_speed == 4);
	assert(td.radar_turn == 0);
	assert(td.radar_max_turn_speed == 45);
	assert(td.gun_turn == 0);
	assert(td.gun_max_turn_speed == 15);
	assert(td.fire == false);
	assert(td.fire_power == 0);
}

void updateTurnData_test()
{
	RubyShip rs("testclass");
	TurnData& td = rs.getTurnData();
	td.energy = 99.0;
	rs.updateTurnData();
	TurnData td2 = rs.getTurnData();
	assert(td.energy == 99);
	assert(td.move == 0);
	assert(td.turn == 0);
	assert(td.max_speed == 8);
	assert(td.max_turn_speed == 4);
	assert(td.radar_turn == 0);
	assert(td.radar_max_turn_speed == 45);
	assert(td.gun_turn == 0);
	assert(td.gun_max_turn_speed == 15);
	assert(td.fire == false);
	assert(td.fire_power == 0);
}

void ship_run_test()
{
	RubyShip rs("testclass");
	assert(rs.run());
	TurnData td = rs.getTurnData();
	assert(td.energy == 100);
	assert(td.move == 100);
	assert(td.turn == 0.2);
	assert(td.max_speed == 8);
	assert(td.max_turn_speed == 4);
	assert(td.radar_turn == 999);
	assert(td.radar_max_turn_speed == 45);
	assert(td.gun_turn == 0);
	assert(td.gun_max_turn_speed == 15);
	assert(td.fire == false);
	assert(td.fire_power == 0);	
}

void scannedRobotEvent_test()
{
	RubyShip rs("testclass");
	assert(rs.onScannedShip(ScannedShipEvent{0.4, 0.1, 100, 33, "Testing", 8}));
	TurnData td = rs.getTurnData();
	assert(td.energy == 100);
	assert(td.move == 100);
	assert(td.turn == 0);
	assert(td.max_speed == 8);
	assert(td.max_turn_speed == 4);
	assert(td.radar_turn == 0);
	assert(td.radar_max_turn_speed == 45);
	assert(td.gun_turn == 0);
	assert(td.gun_max_turn_speed == 15);
	assert(td.fire == false);
	assert(td.fire_power == 0);
}

void hitByBulletEvent_test()
{
	RubyShip rs("testclass");
	assert(rs.onHitByBullet(HitByBulletEvent{RubyBullet("owner_name", 10, 11, 1.5).getID()}));
	TurnData td = rs.getTurnData();
	assert(td.energy == 100);
	assert(td.move == 10);
	assert(td.turn == 0);
	assert(td.max_speed == 8);
	assert(td.max_turn_speed == 4);
	assert(td.radar_turn == 0);
	assert(td.radar_max_turn_speed == 45);
	assert(td.gun_turn == 0);
	assert(td.gun_max_turn_speed == 15);
	assert(td.fire == false);
	assert(td.fire_power == 0);
}

void bulletHitEvent_test()
{
	RubyShip rs("testclass");
	assert(rs.onBulletHit(BulletHitEvent{RubyBullet("owner_name", 10, 11, 2).getID(), "target_name", 80}));
	TurnData td = rs.getTurnData();
	assert(td.energy == 100);
	assert(td.move == 20);
	assert(td.turn == 0);
	assert(td.max_speed == 8);
	assert(td.max_turn_speed == 4);
	assert(td.radar_turn == 0);
	assert(td.radar_max_turn_speed == 45);
	assert(td.gun_turn == 0);
	assert(td.gun_max_turn_speed == 15);
	assert(td.fire == false);
	assert(td.fire_power == 0);
}

void bulletHitBulletEvent_test()
{
	RubyShip rs("testclass");
	assert(rs.onBulletHitBullet(BulletHitBulletEvent{RubyBullet("owner_name", 10, 11, 2).getID(), RubyBullet("owner2_name", 10, 11, 3).getID()}));
	TurnData td = rs.getTurnData();
	assert(td.energy == 100);
	assert(td.move == 30);
	assert(td.turn == 0);
	assert(td.max_speed == 8);
	assert(td.max_turn_speed == 4);
	assert(td.radar_turn == 0);
	assert(td.radar_max_turn_speed == 45);
	assert(td.gun_turn == 0);
	assert(td.gun_max_turn_speed == 15);
	assert(td.fire == false);
	assert(td.fire_power == 0);
}

void shipHitEvent_test()
{
	RubyShip rs("testclass");
	assert(rs.onShipHit(ShipHitEvent{ "RammedShipName", 0.533, 0.0, 89.9, 10 }));
	TurnData td = rs.getTurnData();
	assert(td.energy == 100);
	assert(td.move == 40);
	assert(td.turn == 0);
	assert(td.max_speed == 8);
	assert(td.max_turn_speed == 4);
	assert(td.radar_turn == 0);
	assert(td.radar_max_turn_speed == 45);
	assert(td.gun_turn == 0);
	assert(td.gun_max_turn_speed == 15);
	assert(td.fire == false);
	assert(td.fire_power == 0);
}

int main()
{
	getTurnData_test();
	updateTurnData_test();
	ship_run_test();
	scannedRobotEvent_test();
	hitByBulletEvent_test();
	bulletHitEvent_test();
	bulletHitBulletEvent_test();
	shipHitEvent_test();
	return 0;
}

