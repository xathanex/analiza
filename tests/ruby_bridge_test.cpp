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

void define_ruby_global_method_test()
{
	RubyBridge& rb_bridge = RubyBridge::initialize();
	rb_bridge.define_global_method("getX", getX);
	string s = rb_bridge.exec("getX");
	assert(rb_bridge.last_exec());
	assert(stod(s) == 5.99);
}

void define_ruby_class()
{
	RubyBridge& rb_bridge = RubyBridge::initialize();
	
	rb_bridge.exec("a = A.new");
	assert(!rb_bridge.last_exec());
	rb_bridge.exec("class B < A\nend");
	assert(!rb_bridge.last_exec());
	
	rb_bridge.define_class("A");
	assert(rb_bridge.last_exec());

	rb_bridge.exec("@b = A.new");
	assert(rb_bridge.last_exec());
	rb_bridge.exec("class A\ndef foo\nreturn 2+2\nend\nend");
	assert(rb_bridge.last_exec());
	assert(stod(rb_bridge.exec("@b.foo")) == 4.0);
	assert(rb_bridge.last_exec());

	
	rb_bridge.exec("class B < A\ndef foo\nreturn 3+2\nend\nend");
	rb_bridge.exec("@b = B.new");
	assert(rb_bridge.last_exec());
	assert(stod(rb_bridge.exec("@b.foo")) == 5.0);
	assert(rb_bridge.last_exec());
}

int main()
{
	exec_string_test();
	exec_file_test();
	define_ruby_global_method_test();
	define_ruby_class();
	return 0;
}
