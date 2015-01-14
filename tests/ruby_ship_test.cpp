#include <cassert>
#include "../sources/ruby_ship.h"

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

int main()
{
	getTurnData_test();
	return 0;
}

