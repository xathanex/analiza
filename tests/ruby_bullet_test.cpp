#include <cassert>
#include "../sources/ruby_bullet.h"

using namespace std;

void create_bullet_test()
{
	RubyBridge& bridge = RubyBridge::initialize();
	assert(stoi(bridge.exec("@bullets.count")) == 0);
	RubyBullet* bullet = new RubyBullet("testclass", 10, 11, 2);
	assert(bullet->getID() == 0);
	assert(stoi(bridge.exec("@bullets.count")) == 1);
	assert(stoi(bridge.exec("@bullets.first.getX")) == 10);
	assert(stoi(bridge.exec("@bullets.first.getY")) == 11);
	assert(stoi(bridge.exec("@bullets.first.getPower")) == 2);
	assert(bridge.exec("@bullets.first.getOwnerName") == string("testclass"));
	
	delete bullet;
	assert(stoi(bridge.exec("@bullets.first.nil?")) == 1);
}

int main()
{
	create_bullet_test();
	return 0;
}

