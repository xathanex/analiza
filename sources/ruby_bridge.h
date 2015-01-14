#ifndef RUBY_BRIDGE
#define RUBY_BRIDGE

#include <ruby.h>
#include <string>

using std::string;
typedef VALUE rb_value;
typedef rb_value rb_function;

class RubyBridge
{
public:
	static RubyBridge& initialize(){
		static RubyBridge singleton;
		return singleton;
	}
	
	string exec(const char*);
	string exec(string);
	string exec_file(const char*);
	
	void define_global_method(const char*, rb_value func(int, rb_value*, rb_value));
	rb_value define_class(const char*, rb_value = rb_cObject);
	void define_method(rb_value, const char*, rb_value func(int, rb_value*, rb_value));
	
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
