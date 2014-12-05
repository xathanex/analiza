#ifndef RUBY_BRIDGE
#define RUBY_BRIDGE

class RubyBridge
{
public:
	static RubyBridge& initialize(){
		static RubyBridge singleton;
		return singleton;
	}
	
	bool exec(const char*);
	bool exec_file(const char*);
	const char* exec_method(const char*);
	
	bool last_exec();
	
private:
	RubyBridge();
	RubyBridge(RubyBridge const&);
	RubyBridge& operator=(RubyBridge const&);
	~RubyBridge();
	
	int* last_execution;
};

#endif
