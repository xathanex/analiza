all:
	g++ -O2 -std=c++11 -I /usr/include/ruby-1.9.1/ -I /usr/include/ruby-1.9.1/x86_64-linux/ -lruby -lcrypt -lSDL -lGLU -lGL *.cpp graphics/*.cpp -o ../RubyShips.x

clean:
	rm *~ *.x ../*.x ../*~

run:
	../RubyShips.x
