#ifndef RUBY_BRIDGE
#define RUBY_BRIDGE

#include <ruby.h>
#include <string>

using std::string;
typedef VALUE rb_value;

class RubyBridge
{
public:
	static RubyBridge& initialize(){
		static RubyBridge singleton;
		return singleton;
	}
	
	string exec(const char*);
	string exec_file(const char*);
	
	rb_value declare_method(const char*);
	char* call_method(const char*);
	
	bool last_exec();
	
private:

	RubyBridge();
	RubyBridge(RubyBridge const&);
	RubyBridge& operator=(RubyBridge const&);
	~RubyBridge();
	
	string process_rb_value(rb_value);
	
	int* last_execution;
};

#endif
