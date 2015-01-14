#include "ruby_bridge.h"
#include <fstream>

using std::fstream;
using std::ios;
using std::to_string;

RubyBridge::RubyBridge(): last_execution(new int)
{
	ruby_init();
	ruby_init_loadpath();
	rb_set_safe_level(0);
	ruby_script("embeded_ruby");

  const char* options[]  =  { "", "-enil", 0 };
  ruby_exec_node(ruby_options(2, (char**)options));
}

RubyBridge::~RubyBridge()
{
	ruby_cleanup(0);
}

bool RubyBridge::last_exec(){ return (*last_execution) == 0; }

string RubyBridge::process_rb_value(rb_value v)
{
	string s = "";
	
	if(TYPE(v) == T_NIL){ s = "nil"; }
	else if(TYPE(v) == T_FIXNUM or TYPE(v) == T_FLOAT){ s = to_string(NUM2DBL(v)); }
	else if(TYPE(v) == T_STRING or TYPE(v) == T_SYMBOL){ s = string(RSTRING_PTR(v)); }
	return s;
}

string RubyBridge::exec(const char* instuction)
{
	rb_value result = rb_eval_string_protect(instuction, last_execution);
	string sresult = "";
	if(last_exec()){ sresult = process_rb_value(result);	}
	return sresult;
}

string RubyBridge::exec(string instruction){ return exec(instruction.c_str()); }

string RubyBridge::exec_file(const char* file_name)
{
 	string tmp = "", s = "";
  fstream f;
  f.open(file_name, ios::binary|ios::in);
  while(f.good())
  {
  	getline(f, tmp);
	 	s += tmp+"\n";
  }
  f.close();
	return exec(s.c_str());
}

void RubyBridge::define_global_method(const char* name, rb_value func(int, rb_value*, rb_value))
{
	(*last_execution) = 0;
	rb_define_global_function(name, (rb_value(*)(...))func, -1);
}

rb_value RubyBridge::define_class(const char* name, rb_value super_class)
{
	(*last_execution) = 0;
	return rb_define_class(name, super_class);
}

void RubyBridge::define_method(rb_value klass, const char* name, rb_value func(int, rb_value*, rb_value))
{
	(*last_execution) = 0;
	rb_define_method(klass, name, (rb_value(*)(...))func, -1);
}
