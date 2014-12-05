#include "ruby_bridge.h"
#include <ruby.h>
#include <fstream>
#include <string>

using std::fstream;
using std::ios;
using std::string;

RubyBridge::RubyBridge(): last_execution(new int)
{
	ruby_init();
	ruby_init_loadpath();
	rb_set_safe_level(0);
	ruby_script("embeded ruby");

  const char* options[]  =  { "", "-enil", 0 };
  ruby_exec_node(ruby_options(2, (char**)options));
}

RubyBridge::~RubyBridge()
{
	ruby_cleanup(0);
}

bool RubyBridge::last_exec(){ return (*last_execution) == 0; }

bool RubyBridge::exec(const char* instuction)
{
	rb_eval_string_protect(instuction, last_execution);
	return last_exec();
}

bool RubyBridge::exec_file(const char* file_name)
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
	rb_eval_string_protect(s.c_str(), last_execution);
	return last_exec();
}
