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

struct TestRubyBullet: public RubyBullet
{
	TestRubyBullet(const char* owner, short x, short y, double power): RubyBullet(owner, x, y, power) {}
	void update(short x, short y){ setPos(x, y); }
};

void update_bullet()
{
	RubyBridge& bridge = RubyBridge::initialize();
	assert(stoi(bridge.exec("@bullets.count")) == 1);
	TestRubyBullet bullet("testclass", 10, 11, 2);
	assert(bullet.getID() == 1);
	assert(stoi(bridge.exec("@bullets.count")) == 2);
	assert(stoi(bridge.exec("@bullets.last.getX")) == 10);
	assert(stoi(bridge.exec("@bullets.last.getY")) == 11);
	assert(stoi(bridge.exec("@bullets.last.getPower")) == 2);
	assert(bridge.exec("@bullets.last.getOwnerName") == string("testclass"));
	bullet.update(20, 30);
	assert(stoi(bridge.exec("@bullets.last.getX")) == 20);
	assert(stoi(bridge.exec("@bullets.last.getY")) == 30);

}

int main()
{
	create_bullet_test();
	update_bullet();
	return 0;
}

