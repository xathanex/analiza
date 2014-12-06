#include <cassert>
#include "../sources/ruby_bridge.h"

using namespace std;

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

int main()
{
	exec_string_test();
	exec_file_test();
	return 0;
}
