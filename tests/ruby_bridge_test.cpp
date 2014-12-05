#include <cassert>
#include "../sources/ruby_bridge.h"

using namespace std;

void exec_string_test()
{
	RubyBridge& rb_bridge = RubyBridge::initialize();
	assert(rb_bridge.exec("puts 1+1"));
	assert(rb_bridge.last_exec());
}

void exec_file_test()
{
	RubyBridge& rb_bridge = RubyBridge::initialize();
	assert(rb_bridge.exec_file("test.rb"));
	assert(rb_bridge.last_exec());
}

/*void exec_method_test()
{
	RubyBridge& rb_bridge = RubyBridge::initialize();
	assert(string(rb_bridge.exec_method("foo")) == "20");
	assert(rb_bridge.last_exec());
}*/

int main()
{
	exec_string_test();
	exec_file_test();
	//exec_method_test();
	return 0;
}
