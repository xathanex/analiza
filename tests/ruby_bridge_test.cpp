#include <cassert>
#include "../sources/ruby_bridge.h"

using namespace std;

rb_value getX(int argc, rb_value* argv, rb_value obj){ return rb_float_new(5.99); }

void exec_string_test()
{
	RubyBridge& rb_bridge = RubyBridge::initialize();
	assert(stod(rb_bridge.exec("1+1")) == 2);
	assert(rb_bridge.last_exec());
}

void exec_file_test()
{
	RubyBridge& rb_bridge = RubyBridge::initialize();
	assert(rb_bridge.exec_file("test.rb") == "nil");
	assert(rb_bridge.last_exec());
}

void call_from_ruby_test()
{
	RubyBridge& rb_bridge = RubyBridge::initialize();
	rb_bridge.define_global_method("getX", getX);
	string s = rb_bridge.exec("getX");
	assert(rb_bridge.last_exec());
	assert(stod(s) == 5.99);
}

int main()
{
	exec_string_test();
	exec_file_test();
	call_from_ruby_test();
	return 0;
}
