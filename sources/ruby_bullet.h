#ifndef RUBY_BULLET
#define RUBY_BULLET

#include "ruby_bridge.h"

class RubyBullet
{
public:
	RubyBullet(const char*, short, short, double);
	virtual ~RubyBullet();
	
	unsigned getID() const;
	
	static RubyBridge& bridge;

	void setPos(short, short);

private:
	unsigned id;
};

#endif

